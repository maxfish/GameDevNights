#include <engine/2d_sprites/include/Sprite.h>

Sprite::Sprite(FramesStore *framesStore) {
    _framesStore = framesStore;
    _position.x = _position.y = 0;
    _flags = 0;


    _attack_box = SDL_Rect();
    _hit_box = SDL_Rect();

    _frame = nullptr;
    _animation = nullptr;
    _animation_name = "";
    _animation_frame_index = 0;
    _animation_frame_delay = 0;
    _animating = false;
}

Sprite::~Sprite() {

}

void Sprite::update(float game_speed) {
    updateCollisionBoxes();
    if (!_animating) {
        return;
    }
    if (_animation_frame_delay <= 0) {
        nextAnimationFrame();
        return;
    } else {
        _animation_frame_delay -=game_speed;
    }
}

void Sprite::draw(Graphics &graphics) {
    if (_frame == nullptr) {
        return;
    }

    Uint16 flags = _flags;
    AnimationFrame animation_frame = *_animation->getFrame(_animation_frame_index);
    // Override animation flip if the frame is also flipped
    if (animation_frame.getFlipX()) {
        flags |= FLAG_FLIP_X;
    }
    if (animation_frame.getFlipY()) {
        flags |= FLAG_FLIP_Y;
    }

    int dest_x = _position.x; // TODO: window offset
    int dest_y = _position.y; // TODO: window offset

    _framesStore->drawFrame(graphics, *_frame, dest_x, dest_y, flags);
//
//        # DEBUG boxes
//        if Sprite.DEBUG:
//            if self.hit_box and self.hit_box.w > 0 and self.hit_box.h > 0:
//                pygame.draw.rect(surface, (0, 200, 0), self.hit_box.move(-window_x, -window_y), 1)
//            if self.attack_box and self.attack_box.w > 0 and self.attack_box.h > 0:
//                pygame.draw.rect(surface, (200, 0, 0), self.attack_box.move(-window_x, -window_y), 1)
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
    setAnimationFrame(0);
}

void Sprite::stopAnimation() {
    _animation_frame_delay = 0;
    _animation_frame_index = 0;
    _animating = false;
}

void Sprite::setAnimationFrame(Uint8 frame_index) {
    _animation = _framesStore->getAnimation(_animation_name);
    _animation_frame_index = frame_index;
    AnimationFrame *new_frame = _animation->getFrame(frame_index);
    _animation_frame_delay = (Uint8) new_frame->getDelay();
    _frame = _framesStore->getFrame(new_frame->getFrameName());
}

void Sprite::nextAnimationFrame() {
    Uint8 new_animation_frame_index = (Uint8) (_animation_frame_index + 1);
    if (new_animation_frame_index > _animation->getFramesCount() - 1) {
        if ((_flags & FLAG_LOOP_ANIMATION) == 0) {
            _animating = false;
            return;
        } else {
            new_animation_frame_index = 0;
        }
    }
    setAnimationFrame(new_animation_frame_index);
}

void Sprite::skipToLastAnimationFrame() {
    if (!_animating) {
        return;
    }

    _animating = false;
    setAnimationFrame((Uint8) (_animation->getFramesCount() - 1));
}

void Sprite::updateCollisionBoxes() {
//    def _update_collision_boxes(self):
//        # NOTE: this crashes when there is no animation running
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
