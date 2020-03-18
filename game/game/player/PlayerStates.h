//
// Created by max on 05/03/17.
//

#pragma once

class Player;

class PlayerState {
public:
    constexpr static float32 SPEED_WALK = 3.0;
    constexpr static float32 SPEED_RUN = 4.0;
    constexpr static float32 SPEED_PUSH = 2.0;
    constexpr static float32 IMPULSE_JUMP_H = 14;
    constexpr static float32 IMPULSE_JUMP_V = 65;
    constexpr static float32 SPEED_IN_AIR_H = 3;

    PlayerState(Player *player) { _p = player; };

    virtual ~PlayerState() {}

    virtual void enter(PlayerState *oldState) {}

    virtual void leave(PlayerState *newState) {}

    virtual PlayerState *handleInput(float gameSpeed) { return nullptr; }

    virtual PlayerState *update(float gameSpeed) { return nullptr; }

protected:
    Player *_p;

    void handleInputInAir(float gameSpeed);

    bool hasToFall();
};

class PlayerStateStand : public PlayerState {
public:
    PlayerStateStand(Player *player) : PlayerState(player) {}

    void enter(PlayerState *oldState) override;

    void leave(PlayerState *newState) override;

    PlayerState *handleInput(float gameSpeed) override;

    PlayerState *update(float gameSpeed) override;
};

class PlayerStateWalk : public PlayerState {
public:
    PlayerStateWalk(Player *player) : PlayerState(player) {}

    void enter(PlayerState *oldState) override;

    void leave(PlayerState *newState) override;

    PlayerState *handleInput(float gameSpeed) override;

    PlayerState *update(float gameSpeed) override;

protected:
    bool _pushing;
};

class PlayerStateJump : public PlayerState {
public:
    PlayerStateJump(Player *player) : PlayerState(player) {}

    void enter(PlayerState *oldState) override;

    void leave(PlayerState *newState) override;

    PlayerState *handleInput(float gameSpeed) override;

    PlayerState *update(float gameSpeed) override;
};

class PlayerStateFall : public PlayerState {
public:
    PlayerStateFall(Player *player) : PlayerState(player) {}

    void enter(PlayerState *oldState) override;

    void leave(PlayerState *newState) override;

    PlayerState *handleInput(float gameSpeed) override;

    PlayerState *update(float gameSpeed) override;
};
