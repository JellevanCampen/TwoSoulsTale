#include "TestObject.hpp"
#include "..\src\engine\common\utility\VectorTypes.hpp"

// Constructor (given transform)
GameContent::TestObject::TestObject(Engine::transform3D transform, Engine::aabb3Df aabb)
	: GameObject(transform, aabb)
{

}

// Creates the game object
void GameContent::TestObject::Create()
{
	// Initialize position to the center of the screen
	m_PosX = 128;
	m_PosY = 120;

	m_SpeedX = 0;
	m_SpeedY = 0;

	// Start playing music
	// Engine::AudioResource* mscChina = Engine::AudioManager::GetInstance().LoadAudioResource("music/thunderstruck.flac");
	// Engine::AudioManager::GetInstance().Play(mscChina);

	// Register for listening to input
	Engine::InputManager::GetInstance().RegisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().RegisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().RegisterMousePositionListener(this);
	Engine::InputManager::GetInstance().RegisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().RegisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().RegisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().RegisterGamepadButtonListener(this);

	// Reserve a sprite sheet
	m_SpriteSheetSpiny = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("02 - Super Mario Bros/9CEvO.png");
	m_SpriteSheetGoomba = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("02 - Super Mario Bros/02goomba.png");

	// TESTING
	// Generate a physics world

	// ---- Terrain
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(128.f / scale, -10.0f / scale);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(128.0f / scale, 10.0f / scale);
	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef ceilingBodyDef;
	ceilingBodyDef.position.Set(128.f / scale, 250.0f / scale);
	b2Body* ceilingBody = world.CreateBody(&ceilingBodyDef);
	b2PolygonShape ceilingBox;
	ceilingBox.SetAsBox(128.0f / scale, 10.0f / scale);
	ceilingBody->CreateFixture(&ceilingBox, 0.0f);

	b2BodyDef leftWallDef;
	leftWallDef.position.Set(-10.0f / scale, 120.0f / scale);
	b2Body* leftWallBody = world.CreateBody(&leftWallDef);
	b2PolygonShape leftWallBox;
	leftWallBox.SetAsBox(10.0f / scale, 120.0f / scale);
	leftWallBody->CreateFixture(&leftWallBox, 0.0f);

	b2BodyDef rightWallDef;
	rightWallDef.position.Set((256.0f + 10.0f) / scale, 120.0f / scale);
	b2Body* rightWallBody = world.CreateBody(&rightWallDef);
	b2PolygonShape rightWallBox;
	rightWallBox.SetAsBox(10.0f / scale, 120.0f / scale);
	rightWallBody->CreateFixture(&rightWallBox, 0.0f);

	// ---- Dynamic Objects
	b2PolygonShape dynamicBox;
	b2Vec2 points[4];
	points[0].x = -26.0f / 2.0f / scale;
	points[0].y = 0.0f / 2.0f / scale;
	points[1].x = -26.0f / 2.0f / scale;
	points[1].y = 27.0f / scale;
	points[2].x = 26.0f / 2.0f / scale;
	points[2].y = 27.0f / scale;
	points[3].x = 26.0f / 2.0f / scale;
	points[3].y = 0.0f / 2.0f / scale;
	dynamicBox.Set(points, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(128.0f / scale, 200.0f / scale);
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	b2PolygonShape dynamicDistanceBox;
	b2Vec2 pointsDistance[4];
	pointsDistance[0].x = -20.0f / 2.0f / scale;
	pointsDistance[0].y = 0.0f / 2.0f / scale;
	pointsDistance[1].x = -20.0f / 2.0f / scale;
	pointsDistance[1].y = 23.0f / scale;
	pointsDistance[2].x = 20.0f / 2.0f / scale;
	pointsDistance[2].y = 23.0f / scale;
	pointsDistance[3].x = 20.0f / 2.0f / scale;
	pointsDistance[3].y = 0.0f / 2.0f / scale;
	dynamicDistanceBox.Set(pointsDistance, 4);

	b2FixtureDef fixtureDistanceDef;
	fixtureDistanceDef.shape = &dynamicDistanceBox;
	fixtureDistanceDef.density = 1.0f;
	fixtureDistanceDef.friction = 0.3f;
	fixtureDistanceDef.restitution = 0.5f;

	b2BodyDef bodyDistanceDef;
	bodyDistanceDef.type = b2_dynamicBody;
	bodyDistanceDef.position.Set(128.0f / scale, 120.0f / scale);
	bodyDistanceDef.linearDamping = 0.1f;
	bodyDistanceDef.angularDamping = 0.1f;
	bodyDistance = world.CreateBody(&bodyDistanceDef);
	bodyDistance->CreateFixture(&fixtureDistanceDef);

	b2DistanceJointDef distanceJointDef;
	distanceJointDef.Initialize(ceilingBody, bodyDistance, ceilingBody->GetPosition(), bodyDistance->GetPosition());
	distanceJointDef.collideConnected = true;
	distanceJointDef.frequencyHz = 4.0f;
	distanceJointDef.dampingRatio = 1.0f;
	b2DistanceJoint* distanceJoint = (b2DistanceJoint*)world.CreateJoint(&distanceJointDef);
	
	m_AlarmSlow = Engine::TimingManager::GetInstance().SetAlarm(500000, 20);
	m_AlarmFast = Engine::TimingManager::GetInstance().SetAlarm(5000, 20);
	m_AlarmOnce = Engine::TimingManager::GetInstance().SetAlarm(1234000);
	m_AlarmInfinite = Engine::TimingManager::GetInstance().SetAlarm(500000, (unsigned int)(-1));
	Engine::TimingManager::GetInstance().RegisterAlarmListener(m_AlarmSlow, this);
	Engine::TimingManager::GetInstance().RegisterAlarmListener(m_AlarmFast, this);
	Engine::TimingManager::GetInstance().RegisterAlarmListener(m_AlarmOnce, this);
	Engine::TimingManager::GetInstance().RegisterAlarmListener(m_AlarmInfinite, this);

	m_Circle = Engine::circled(64.0, 64.0, 24.0);
	m_Ray = Engine::ray2Dd(0.0, 256.0, 0.0, 256.0);
	// TESTING
}

// Destroys the game object
void GameContent::TestObject::Destroy()
{
	// Deregister input listening
	Engine::InputManager::GetInstance().DeregisterKeyboardKeyListener(this);
	Engine::InputManager::GetInstance().DeregisterKeyboardCharacterListener(this);
	Engine::InputManager::GetInstance().DeregisterMousePositionListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseEnterLeaveListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseButtonListener(this);
	Engine::InputManager::GetInstance().DeregisterMouseScrollListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadAxisListener(this);
	Engine::InputManager::GetInstance().DeregisterGamepadButtonListener(this);

	// Free a sprite sheet
	Engine::ResourceManager::GetInstance().FreeSpriteSheet(m_SpriteSheetSpiny);
	Engine::ResourceManager::GetInstance().FreeSpriteSheet(m_SpriteSheetGoomba);
}

// Updates the game object
void GameContent::TestObject::Update(const Engine::GameTime& gameTime)
{
	// Update the position
	m_PosX += m_SpeedX * ((float)gameTime.deltaTimeMicros / 10000.f);
	m_PosY += m_SpeedY * ((float)gameTime.deltaTimeMicros / 10000.f);

	// TESTING
	world.Step(timestep, velocityIterations, positionIterations);
	world.ClearForces(); // Needed to reset forces if they were applied during the previous update

	Engine::f2 bodyPos = Engine::f2(body->GetPosition().x * scale, body->GetPosition().y * scale);
	Engine::f2 centerPos = Engine::f2(256.0f / 2.0f, 240.0f / 2.0f);
	Engine::GraphicsManager::GetInstance().SetCameraPosition(Engine::f2((bodyPos.x() + 3.0f * centerPos.x()) / 4.0f, (bodyPos.y() + 3.0f * centerPos.y()) / 4.0f));
	float test = Engine::f2(bodyPos - centerPos).Length();
	float temp = 4.0f - 0.5f * Engine::f2(bodyPos - centerPos).Length() / 128.0f;
	Engine::GraphicsManager::GetInstance().SetCameraZoom(temp);
	m_Transform.t(Engine::f3(bodyPos, 0.0f));
	// TESTING
	
	if ((gameTime.frameCount % 500) == 499)
	{
		Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "FPS: " + std::to_string(gameTime.frameCount * 1000000 / (gameTime.totalTimeMicros)));
		// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "FPS: " + std::to_string(1000000.f / gameTime.deltaTimeMicros));
	}

	m_Ray.p2().x(fmod(gameTime.totalTimeMicros / 50000.0, 256.0));
	m_Ray.p2().y(256.0f - m_Ray.p2().x());
}

// Draws the game object
void GameContent::TestObject::Draw(const Engine::GameTime& gameTime)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Drawing TestObject.");
	// Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrame(m_SpriteSheet, 6 + (gameTime.totalTimeMicros / 100000) % 5, m_PosX, m_PosY, 0);
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrameTransformed(m_SpriteSheetSpiny, 6 + (gameTime.totalTimeMicros / 100000) % 5, body->GetPosition().x * scale, body->GetPosition().y * scale, 0, body->GetAngle(), 1.0f, 1.0f);
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrameTransformed(m_SpriteSheetGoomba, 0 + (gameTime.totalTimeMicros / 100000) % 4, bodyDistance->GetPosition().x * scale, bodyDistance->GetPosition().y * scale, 0, bodyDistance->GetAngle(), 1.0f, 1.0f);

	Engine::GraphicsManager::GetInstance().DrawLine(Engine::f2(128.0f, 240.0f), Engine::f2(bodyDistance->GetPosition().x * scale, bodyDistance->GetPosition().y * scale), Engine::f4(0.2f, 0.2f, 1.0f, 1.0f));

	// Engine::GraphicsManager::GetInstance().DrawRectangle(Engine::aabb2Df(m_Circle.p().x() - m_Circle.r(), m_Circle.p().x() + m_Circle.r(), m_Circle.p().y() - m_Circle.r(), m_Circle.p().y() + m_Circle.r()), Engine::f4(0.4f, 0.4f, 1.0f, 1.0f));
	Engine::GraphicsManager::GetInstance().DrawCircle(m_Circle, Engine::f4(0.4f, 0.4f, 1.0f, 1.0f));

	Engine::f4 color(0.4f, 1.0f, 0.4f, 1.0f);
	Engine::d2 enter, exit;
	if (Engine::CollisionManager::GetInstance().IsIntersecting(m_Ray, m_Circle, enter, exit)) 
	{ 	
		Engine::GraphicsManager::GetInstance().DrawRectangle(Engine::aabb2Df((Engine::f2)(enter - Engine::d2(1.0f)), (Engine::f2)(enter + Engine::d2(1.0f))), Engine::f4(1.0f, 0.5f, 0.5f, 1.0f));
		Engine::GraphicsManager::GetInstance().DrawRectangle(Engine::aabb2Df((Engine::f2)(exit - Engine::d2(1.0f)), (Engine::f2)(exit + Engine::d2(1.0f))), Engine::f4(1.0f, 0.5f, 0.5f, 1.0f));
	}
	
	if (Engine::CollisionManager::GetInstance().IsIntersecting(m_Ray, m_Circle))
	{
		color = Engine::f4(1.0f, 0.4f, 0.4f, 1.0f);
	}
	Engine::GraphicsManager::GetInstance().DrawLine(m_Ray.p1(), m_Ray.p2(), color);

	Engine::circled collCircle(0.0, 0.0, 8.0);
	color = Engine::f4(0.4f, 1.0f, 0.4f, 1.0f);
	if (Engine::CollisionManager::GetInstance().IsIntersecting(collCircle, m_Circle, m_Ray.p2(), enter, exit))
	{
		color = Engine::f4(1.0f, 0.4f, 0.4f, 1.0f);
		Engine::GraphicsManager::GetInstance().DrawCircle(Engine::circled(enter, collCircle.r()), Engine::f4(0.4f, 0.4f, 1.0f, 1.0f));
		Engine::GraphicsManager::GetInstance().DrawCircle(Engine::circled(exit, collCircle.r()), Engine::f4(0.4f, 0.4f, 1.0f, 1.0f));
	}
}

/**************************************************************/
/* Input events                                               */
/**************************************************************/

void GameContent::TestObject::ProcessKeyboardKeyEvent(int key, Engine::KeyboardListener::KeyboardKeyAction action)
{
	/*if (key == GLFW_KEY_LEFT && action == KeyboardKeyAction::PRESSED) m_SpeedX -= 1;
	if (key == GLFW_KEY_LEFT && action == KeyboardKeyAction::RELEASED) m_SpeedX += 1;

	if (key == GLFW_KEY_RIGHT && action == KeyboardKeyAction::PRESSED) m_SpeedX += 1;
	if (key == GLFW_KEY_RIGHT && action == KeyboardKeyAction::RELEASED) m_SpeedX -= 1;

	if (key == GLFW_KEY_DOWN && action == KeyboardKeyAction::PRESSED) m_SpeedY -= 1;
	if (key == GLFW_KEY_DOWN && action == KeyboardKeyAction::RELEASED) m_SpeedY += 1;

	if (key == GLFW_KEY_UP && action == KeyboardKeyAction::PRESSED) m_SpeedY += 1;
	if (key == GLFW_KEY_UP && action == KeyboardKeyAction::RELEASED) m_SpeedY -= 1;*/

	if (key == GLFW_KEY_UP && action == KeyboardKeyAction::PRESSED)	body->ApplyLinearImpulse(b2Vec2(0.0f, 5.0f), body->GetPosition() + b2Vec2(0.0f / scale, 0.0f / scale), true);
	if (key == GLFW_KEY_LEFT && action == KeyboardKeyAction::PRESSED) body->ApplyLinearImpulse(b2Vec2(-2.0f, 2.0f), body->GetPosition() + b2Vec2(16.0f / scale, 0.25f / scale), true);
	if (key == GLFW_KEY_RIGHT && action == KeyboardKeyAction::PRESSED) body->ApplyLinearImpulse(b2Vec2(2.0f, 2.0f), body->GetPosition() + b2Vec2(-16.0f / scale, 0.25f / scale), true);

	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard key event detected by TestObject.");
}

void GameContent::TestObject::ProcessKeyboardCharacterEvent(unsigned int character)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Keyboard character event detected by TestObject.");
}

void GameContent::TestObject::ProcessMousePositionEvent(double xPos, double yPos)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse position event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseEnterLeaveEvent(bool entered)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse enter/leave event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseButtonEvent(int button, MouseButtonAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse button event detected by TestObject.");
}

void GameContent::TestObject::ProcessMouseScrollEvent(double xOffset, double yOffset)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Mouse scroll event detected by TestObject.");
}

void GameContent::TestObject::ProcessGamepadAxisEvent(unsigned char gamepad, int axis, float axisState)
{
	// Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad axis event detected by TestObject.");
	
	if (fabs(axisState) > 0.2f){
		if (axis == 0)
		{
			m_SpeedX = axisState  * 2.0f;
		}

		if (axis == 1)
		{
			m_SpeedY = -axisState * 2.0f;
		}
	}
	else
	{
		if (axis == 0)
		{
			m_SpeedX = 0.0f;
		}

		if (axis == 1)
		{
			m_SpeedY = 0.0f;
		}
	}
}

void GameContent::TestObject::ProcessGamepadButtonEvent(unsigned char gamepad, int button, GamepadButtonAction action)
{
	Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "Gamepad button event detected by TestObject.");
}

void GameContent::TestObject::ProcessAlarmEvent(Engine::AlarmID alarmID, Engine::Timestamp timestamp)
{
	if (alarmID == m_AlarmSlow) { Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "HEY LISTEN! (slow) @ " + std::to_string(timestamp)); }
	if (alarmID == m_AlarmFast) { Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "HEY LISTEN! (fast) @ " + std::to_string(timestamp)); }
	if (alarmID == m_AlarmOnce) { Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "HEY LISTEN! (once) @ " + std::to_string(timestamp)); }
	if (alarmID == m_AlarmInfinite) { Engine::LoggingManager::GetInstance().Log(Engine::LoggingManager::LogType::Status, "HEY LISTEN! (infinite) @ " + std::to_string(timestamp)); }
}