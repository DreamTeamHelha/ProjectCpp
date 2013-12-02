greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia


DEFINES += SFML_STATIC

QMAKE_CXX += -std=gnu++11

DESTDIR = $$PWD/SirtoliRacing

SOURCES += \
    main.cpp \
    scene.cpp \
    playerinput.cpp \
    box.cpp \
    Box2D/Collision/Shapes/b2PolygonShape.cpp \
    Box2D/Collision/Shapes/b2EdgeShape.cpp \
    Box2D/Collision/Shapes/b2CircleShape.cpp \
    Box2D/Collision/Shapes/b2ChainShape.cpp \
    Box2D/Collision/b2TimeOfImpact.cpp \
    Box2D/Collision/b2DynamicTree.cpp \
    Box2D/Collision/b2Distance.cpp \
    Box2D/Collision/b2Collision.cpp \
    Box2D/Collision/b2CollidePolygon.cpp \
    Box2D/Collision/b2CollideEdge.cpp \
    Box2D/Collision/b2CollideCircle.cpp \
    Box2D/Collision/b2BroadPhase.cpp \
    Box2D/Common/b2Timer.cpp \
    Box2D/Common/b2StackAllocator.cpp \
    Box2D/Common/b2Settings.cpp \
    Box2D/Common/b2Math.cpp \
    Box2D/Common/b2Draw.cpp \
    Box2D/Common/b2BlockAllocator.cpp \
    Box2D/Dynamics/b2WorldCallbacks.cpp \
    Box2D/Dynamics/b2World.cpp \
    Box2D/Dynamics/b2Island.cpp \
    Box2D/Dynamics/b2Fixture.cpp \
    Box2D/Dynamics/b2ContactManager.cpp \
    Box2D/Dynamics/b2Body.cpp \
    Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    Box2D/Dynamics/Contacts/b2Contact.cpp \
    Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    Box2D/Dynamics/Joints/b2Joint.cpp \
    Box2D/Dynamics/Joints/b2GearJoint.cpp \
    Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    Box2D/Rope/b2Rope.cpp \
    car.cpp \
    vector.cpp \
    rotation.cpp \
    gamewindow.cpp \
    SFML/System/Time.cpp \
    object.cpp \
    tilemap.cpp \
    tree.cpp \
    tilemaploader.cpp \
    objectfactories.cpp \
    checkpoint.cpp \
    checkpointlistener.cpp \
    objectloader.cpp \
    gamewidget.cpp \
    menu.cpp \
    formtools.cpp \
    mainwindow.cpp \
    menuingame.cpp \
    view.cpp \
    panel.cpp \
    score.cpp \
    pausemenu.cpp \
    credits.cpp \
    tracklist.cpp \
    choosewidget.cpp

HEADERS += \
    scene.h \
    playerinput.h \
    box.h\
    Box2D/Box2D.h \
    Box2D/Collision/Shapes/b2Shape.h \
    Box2D/Collision/Shapes/b2PolygonShape.h \
    Box2D/Collision/Shapes/b2EdgeShape.h \
    Box2D/Collision/Shapes/b2CircleShape.h \
    Box2D/Collision/Shapes/b2ChainShape.h \
    Box2D/Collision/b2TimeOfImpact.h \
    Box2D/Collision/b2DynamicTree.h \
    Box2D/Collision/b2Distance.h \
    Box2D/Collision/b2Collision.h \
    Box2D/Collision/b2BroadPhase.h \
    Box2D/Common/b2Timer.h \
    Box2D/Common/b2StackAllocator.h \
    Box2D/Common/b2Settings.h \
    Box2D/Common/b2Math.h \
    Box2D/Common/b2GrowableStack.h \
    Box2D/Common/b2Draw.h \
    Box2D/Common/b2BlockAllocator.h \
    Box2D/Dynamics/b2WorldCallbacks.h \
    Box2D/Dynamics/b2World.h \
    Box2D/Dynamics/b2TimeStep.h \
    Box2D/Dynamics/b2Island.h \
    Box2D/Dynamics/b2Fixture.h \
    Box2D/Dynamics/b2ContactManager.h \
    Box2D/Dynamics/b2Body.h \
    Box2D/Dynamics/Contacts/b2PolygonContact.h \
    Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
    Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
    Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
    Box2D/Dynamics/Contacts/b2ContactSolver.h \
    Box2D/Dynamics/Contacts/b2Contact.h \
    Box2D/Dynamics/Contacts/b2CircleContact.h \
    Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
    Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
    Box2D/Dynamics/Joints/b2WheelJoint.h \
    Box2D/Dynamics/Joints/b2WeldJoint.h \
    Box2D/Dynamics/Joints/b2RopeJoint.h \
    Box2D/Dynamics/Joints/b2RevoluteJoint.h \
    Box2D/Dynamics/Joints/b2PulleyJoint.h \
    Box2D/Dynamics/Joints/b2PrismaticJoint.h \
    Box2D/Dynamics/Joints/b2MouseJoint.h \
    Box2D/Dynamics/Joints/b2Joint.h \
    Box2D/Dynamics/Joints/b2GearJoint.h \
    Box2D/Dynamics/Joints/b2FrictionJoint.h \
    Box2D/Dynamics/Joints/b2DistanceJoint.h \
    Box2D/Rope/b2Rope.h \
    car.h \
    vector.h \
    rotation.h \
    gamewindow.h \
    SFML/System/Time.hpp \
    SFML/System/Export.hpp \
    SFML/Config.hpp \
    object.h \
    tilemap.h \
    objectfactory.h \
    tree.h \
    tilemaploader.h \
    objectfactories.h \
    checkpoint.h \
    checkpointlistener.h \
    objectloader.h \
    utils.h \
    gamewidget.h \
    menu.h \
    mainwindow.h \
    menuingame.h \
    view.h \
    panel.h \
    score.h \
    pausemenu.h \
    formtools.h \
    credits.h \
    tracklist.h \
    choosewidget.h

FORMS += \
    gamewindow.ui \
    formtools.ui \
    mainwindow.ui \
    menu.ui \
    menuingame.ui \
    credits.ui \
    choosewidget.ui
