//
// Created by max on 05/03/17.
//

#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "ContactListener.h"
#include "FixtureUserData.h"

void ContactListener::BeginContact(b2Contact *contact) {
    void *fixtureDataA = contact->GetFixtureA()->GetUserData();
    void *fixtureDataB = contact->GetFixtureB()->GetUserData();

    if (fixtureDataA) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataA;
        if (userData ->contactListener) {
            userData->contactListener->BeginContact(contact);
        } else {
            userData->num_contacts++;
        }
    }

    if (fixtureDataB) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataB;
        if (userData ->contactListener) {
            userData->contactListener->BeginContact(contact);
        } else {
            userData->num_contacts++;
        }
    }
}

void ContactListener::EndContact(b2Contact *contact) {
    void *fixtureDataA = contact->GetFixtureA()->GetUserData();
    void *fixtureDataB = contact->GetFixtureB()->GetUserData();

    if (fixtureDataA) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataA;
        if (userData ->contactListener) {
            userData->contactListener->EndContact(contact);
        } else {
            userData->num_contacts--;
        }
    }

    if (fixtureDataB) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataB;
        if (userData ->contactListener) {
            userData->contactListener->EndContact(contact);
        } else {
            userData->num_contacts--;
        }
    }
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);

    void *fixtureDataA = contact->GetFixtureA()->GetUserData();
    void *fixtureDataB = contact->GetFixtureB()->GetUserData();
    if (fixtureDataA) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataA;
        if (userData ->contactListener) {
            userData->contactListener->PreSolve(contact, oldManifold);
        }
    }
    if (fixtureDataB) {
        FixtureUserData *userData = (FixtureUserData *) fixtureDataB;
        if (userData ->contactListener) {
            userData->contactListener->PreSolve(contact, oldManifold);
        }
    }
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
    b2ContactListener::PostSolve(contact, impulse);
}
