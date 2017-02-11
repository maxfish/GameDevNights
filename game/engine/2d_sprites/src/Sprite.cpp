#include <engine/2d_sprites/include/Sprite.h>

Sprite::Sprite(FramesStore *frames_store) {
    _frames_store = frames_store;
    _position.x = _position.y = 0;
    _flags = 0;
    _alpha = SDL_ALPHA_OPAQUE;

    _attack_box = SDL_Rect();
    _hit_box = SDL_Rect();

    _frame = nullptr;
    _animation = nullptr;
    _animation_name = "";
    _animation_frame_index = 0;
    _animation_frame_delay = 0;
    _animating = false;

    _blink_enabled = false;
}

Sprite::~Sprite() {

}

void Sprite::update(float game_speed) {
    if (!_animating) {
        return;
    }

    if (_blink_enabled) {
        _blink_counter += game_speed;
    }

    if (_animation_frame_delay <= 0) {
        _nextAnimationFrame();
        _updateCollisionBoxes();
        return;
    } else {
        _animation_frame_delay -= game_speed;
    }
}

void Sprite::_drawFrame(Graphics &graphics, Frame &frame, int dest_x, int dest_y, Uint16 flags) {
    SDL_Texture *texture = frame.getImage();
    SDL_Rect source_rect = frame.getRect();
    SDL_Point anchor = frame.getAnchor();
    SDL_RendererFlip flipFlags = SDL_FLIP_NONE;
    float destination_angle = 0;

    int anchor_x = frame.getAnchor().x;
    // If flip_x is enabled, the anchor needs to be adjusted
    if ((flags & Sprite::FLAG_FLIP_X) > 0) {
        anchor_x = source_rect.w - anchor_x;
        flipFlags = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect destination_rect = {dest_x - anchor_x, dest_y - anchor.y, source_rect.w, source_rect.h};

    SDL_SetTextureAlphaMod(texture, _alpha);
    SDL_RenderCopyEx(graphics.getRenderer(),
                     texture,
                     &source_rect,
                     &destination_rect,
                     destination_angle,
                     &anchor,
                     flipFlags
    );

    if (DEBUG_ON) {
        SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 255);
        SDL_RenderDrawRect(graphics.getRenderer(), &destination_rect);
    }
}

void Sprite::draw(Graphics &graphics) {
    if (_frame == nullptr) {
        return;
    }

    if (_blink_enabled && _blink_counter>=_blink_frequency) {
        _blink_counter = 0;
        return;
    }

    Uint16 flags = _flags;
    AnimationFrame animation_frame = *_animation->getFrame(_animation_frame_index);
    // Override animation flip if the frame is also flipped
    if (animation_frame.getFlipX()) {
        flags |= FLAG_FLIP_X;
    }

    _drawFrame(graphics, *_frame, _position.x, _position.y, flags);

    // DEBUG boxes
    if (DEBUG_ON) {
//        if self.hit_box and self.hit_box.w > 0 and self.hit_box.h > 0:
//            pygame.draw.rect(surface, (0, 200, 0), self.hit_box.move(-window_x, -window_y), 1)
//        if self.attack_box and self.attack_box.w > 0 and self.attack_box.h > 0:
//            pygame.draw.rect(surface, (200, 0, 0), self.attack_box.move(-window_x, -window_y), 1)
    }
}

void Sprite::setPosition(int x, int y) {
    this->_position.x = x;
    this->_position.y = y;
}

void Sprite::playAnimation(std::string animation_name, Uint16 flags = 0) {
    // If the same animation is already looping, break
    if ((_flags & FLAG_LOOP_ANIMATION) > 0 and _flags == flags and animation_name.compare(_animation_name) == 0) {
        return;
    }

    _animating = true;
    _animation_name = animation_name;
    _flags = flags;
    _setAnimationFrame(0);
}

void Sprite::stopAnimation() {
    _animation_frame_delay = 0;
    _animation_frame_index = 0;
    _animating = false;
}

void Sprite::startBlinking(float frequency) {
    _blink_frequency = frequency;
    _blink_counter = 0;
    _blink_enabled = true;
}

void Sprite::stopBlinking() {
    _blink_enabled = false;
}

void Sprite::setAlpha(Uint8 alpha) {
    _alpha = alpha;
}


void Sprite::_setAnimationFrame(Uint8 frame_index) {
    _animation = _frames_store->getAnimation(_animation_name);
    _animation_frame_index = frame_index;
    AnimationFrame *new_frame = _animation->getFrame(frame_index);
    _animation_frame_delay = (Uint8) new_frame->getDelay();
    _frame = _frames_store->getFrame(new_frame->getFrameName());
}

void Sprite::_nextAnimationFrame() {
    Uint8 new_animation_frame_index = Uint8(_animation_frame_index + 1);
    if (new_animation_frame_index > _animation->getFramesCount() - 1) {
        if ((_flags & FLAG_LOOP_ANIMATION) == 0) {
            _animating = false;
            return;
        } else {
            new_animation_frame_index = 0;
        }
    }
    _setAnimationFrame(new_animation_frame_index);
}

void Sprite::_skipToLastAnimationFrame() {
    if (!_animating) {
        return;
    }

    _animating = false;
    _setAnimationFrame(Uint8(_animation->getFramesCount() - 1));
}

void Sprite::_updateCollisionBoxes() {
//        # TODO: flip_y should be handled as well
//        animation_frame = self.animation.frames[self.animation_frame_index]
//        flip_x = ((self.flags & FramesStore.FLAG_FLIP_X) > 0) ^ animation_frame.flip_x
//
//        if self.frame.hit_box:
//            self.hit_box = self.frame.hit_box.copy()
//            if flip_x:
//                self.hit_box.left = - self.hit_box.left - self.hit_box.width
//            self.hit_box.move_ip(self.x, self.y)
//        else:
//            self.hit_box = None
//
//        if self.frame.attack_box:
//            self.attack_box = self.frame.attack_box.copy()
//            if flip_x:
//                self.attack_box.left = - self.attack_box.left - self.attack_box.width
//            self.attack_box.move_ip(self.x, self.y)
//        else:
//            self.attack_box = None
}

//    def set_frame(self, frame_name):
//        self.stop_animation()
//        self.animation = None
//        self.frame = self.sprite_bank.get_frame(frame_name)
//
//
//    def previous_animation_frame(self):
//        new_animation_frame_index = self.animation_frame_index - 1
//        if new_animation_frame_index < 0:
//            new_animation_frame_index = len(self.animation.frames) - 1
//
//        self._set_animation_frame(new_animation_frame_index)
//
