#include "TestImageResource.hpp"

// Constructor (given transform)
GameContent::TestImageResource::TestImageResource(Engine::transform3D transform)
	: GameObject(transform, Engine::aabb2Df(0, 0, 16, 16))
	, m_FilterIndex(0)
{
	
}

// Creates the game object
void GameContent::TestImageResource::Create()
{
	// Reserve sprite sheet
	m_SpriteSheetGoomba = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("goomba.png");

	// Set an alarm for applying filters
	m_FilterAlarm = Engine::TimingManager::GetInstance().SetInfinitePeriodicAlarm(2000000);
	Engine::TimingManager::GetInstance().RegisterAlarmListener(m_FilterAlarm, this);
}

// Destroys the game object
void GameContent::TestImageResource::Destroy()
{
	
}

// Updates the game object
void GameContent::TestImageResource::Update(const Engine::GameTime& gameTime)
{
	
}

// Draws the game object
void GameContent::TestImageResource::Draw(const Engine::GameTime& gameTime)
{
	Engine::GraphicsManager::GetInstance().DrawSpriteSheetFrame(m_SpriteSheetGoomba, 8 + ((unsigned int)(gameTime.GetTotalTimeSeconds() * 8) % 8) , tf());
}

// Switch filters when the filteralarm is triggered
void GameContent::TestImageResource::ProcessAlarmEvent(Engine::AlarmID alarmID, Engine::Timestamp timestamp)
{
	// Reload the sprite sheet
	Engine::ResourceManager::GetInstance().FreeSpriteSheet(m_SpriteSheetGoomba);
	m_SpriteSheetGoomba = Engine::ResourceManager::GetInstance().ReserveSpriteSheet("goomba.png");

	// Get the image associated to the spritesheet
	Engine::SpriteSheetResource& ss = Engine::ResourceManager::GetInstance().GetSpriteSheetResource(m_SpriteSheetGoomba);
	Engine::ImageResource& im = Engine::ResourceManager::GetInstance().GetImageResource(ss.GetImage());
	Engine::LoggingManager& l = Engine::LoggingManager::GetInstance();

	// Apply a filter
	switch (m_FilterIndex % 25)
	{
	case 0:
		l.Log(Engine::LoggingManager::Status, "Brightening.");
		im.AdjustBrightness(50.0);
		break;
	case 1:
		l.Log(Engine::LoggingManager::Status, "Darkening.");
		im.AdjustBrightness(-50.0);
		break;
	case 2:
		l.Log(Engine::LoggingManager::Status, "Increasing contrast.");
		im.AdjustContrast(50.0);
		break;
	case 3:
		l.Log(Engine::LoggingManager::Status, "Lowering contrast.");
		im.AdjustContrast(-50.0);
		break;
	case 4:
		l.Log(Engine::LoggingManager::Status, "Setting gamma to 2.");
		im.AdjustGamma(2.0);
		break;
	case 5:
		l.Log(Engine::LoggingManager::Status, "Setting gamma to 0.5.");
		im.AdjustGamma(0.5);
		break;
	case 6:
		l.Log(Engine::LoggingManager::Status, "Flipping horizontally.");
		im.FlipHorizontal();
		break;
	case 7:
		l.Log(Engine::LoggingManager::Status, "Flipping vertically.");
		im.FlipVertical();
		break;
	case 8:
		l.Log(Engine::LoggingManager::Status, "Inverting colors.");
		im.InvertColors();
		break;
	case 9:
		l.Log(Engine::LoggingManager::Status, "Scaling down using nearest neighbor filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::NEAREST_NEIGHBOR);
		break;
	case 10:
		l.Log(Engine::LoggingManager::Status, "Scaling down using bilinear filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BILINEAR);
		break;
	case 11:
		l.Log(Engine::LoggingManager::Status, "Scaling down using bicubic filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BICUBIC);
		break;
	case 12:
		l.Log(Engine::LoggingManager::Status, "Scaling down using b-spline filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BSPLINE);
		break;
	case 13:
		l.Log(Engine::LoggingManager::Status, "Scaling down using Catmull-Rom filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::CATMULLROM);
		break;
	case 14:
		l.Log(Engine::LoggingManager::Status, "Scaling down using Lanczos filtering.");
		im.Rescale(Engine::i2(120, 102), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::LANCZOS);
		break;
	case 15:
		l.Log(Engine::LoggingManager::Status, "Scaling up using nearest neighbor filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::NEAREST_NEIGHBOR);
		break;
	case 16:
		l.Log(Engine::LoggingManager::Status, "Scaling down using bilinear filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BILINEAR);
		break;
	case 17:
		l.Log(Engine::LoggingManager::Status, "Scaling down using bicubic filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BICUBIC);
		break;
	case 18:
		l.Log(Engine::LoggingManager::Status, "Scaling down using b-spline filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::BSPLINE);
		break;
	case 19:
		l.Log(Engine::LoggingManager::Status, "Scaling down using Catmull-Rom filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::CATMULLROM);
		break;
	case 20:
		l.Log(Engine::LoggingManager::Status, "Scaling down using Lanczos filtering.");
		im.Rescale(Engine::i2(480, 406), Engine::ImageResource::RescalePolicy::MATCH_DIMENSIONS, Engine::ImageResource::ResampleFilter::LANCZOS);
		break;
	case 21:
		l.Log(Engine::LoggingManager::Status, "Rotating the image clockwise by 90 degrees");
		im.Rotate(Engine::ImageResource::RotationAngle::CW_90);
		break;
	case 22:
		l.Log(Engine::LoggingManager::Status, "Rotating the image clockwise by 180 degrees");
		im.Rotate(Engine::ImageResource::RotationAngle::CW_180);
		break;
	case 23:
		l.Log(Engine::LoggingManager::Status, "Rotating the image counter-clockwise by 90 degrees");
		im.Rotate(Engine::ImageResource::RotationAngle::CCW_90);
		break;
	case 24:
		l.Log(Engine::LoggingManager::Status, "Rotating the image counter-clockwise by 50 degrees");
		im.Rotate(50.0);
		break;
	}

	m_FilterIndex++;
}