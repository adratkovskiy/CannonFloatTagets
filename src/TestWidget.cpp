#include "stdafx.h"
#include "TestWidget.h"

void DrawCross(int x, int y) // инструмент, чтобы понять, про какие координаты идет речь
{
	Render::DrawLine(math::Vector3(x - 10, y, 1), math::Vector3(x + 10, y, 1));
	Render::DrawLine(math::Vector3(x, y - 10, 1), math::Vector3(x, y + 10, 1));
}

void DrawCross(FPoint coords) // инструмент, чтобы понять, про какие координаты идет речь
{
	Render::DrawLine(math::Vector3(coords.x - 10, coords.y, 1), math::Vector3(coords.x + 10, coords.y, 1));
	Render::DrawLine(math::Vector3(coords.x, coords.y - 10, 1), math::Vector3(coords.x, coords.y + 10, 1));
}

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _effParticleSmoke(NULL)
	, _gameTimer(0.f)
{
	Init();
}

void TestWidget::Init()
{
	_backgroundTexture = Core::resourceManager.Get<Render::Texture>("Background");
	_cannonballTexture = Core::resourceManager.Get<Render::Texture>("Cannonball");
	_buttonUpTexture = Core::resourceManager.Get<Render::Texture>("Button_up");
	_buttonDownTexture = Core::resourceManager.Get<Render::Texture>("Button_down");
	_invaderTexture_0 = Core::resourceManager.Get<Render::Texture>("Invader_0");
	_invaderTexture_1 = Core::resourceManager.Get<Render::Texture>("Invader_1");
	_invaderTexture_2 = Core::resourceManager.Get<Render::Texture>("Invader_2");
	_invaderTexture_3 = Core::resourceManager.Get<Render::Texture>("Invader_3");
	_invaderTexture_4 = Core::resourceManager.Get<Render::Texture>("Invader_4");

	_playerTexture = Core::resourceManager.Get<Render::Texture>("Player");

	_options = new Options("base_p/Options.xml");
	_levels = new Options("base_p/Level.xml");
	_gControl = new GameController(GameController::GameStates::START_SCREEN, true, _options->getParamFloat("sys_timer"));
	_targetVPadding = _options->getParamFloat("target_vert_padding");
	_targetHPadding = _options->getParamFloat("target_horiz_padding");
	_topPadding = _options->getParamFloat("target_top_padding");
	_targetScale = _options->getParamFloat("target_scale");
	_targetSize = (FRect)_invaderTexture_0->getBitmapRect();
	_gameScreen = _options->getParamFPoint("game_screen");
	_topBorder = _options->getParamInt("border_top");
	_bottomBorder = _options->getParamInt("border_bottom");
	_leftBorder = _options->getParamInt("border_left");
	_rightBorder = _options->getParamInt("border_right");
	_gamePoints = _options->getParamInt("game_points_default");
	_gameTimer = _options->getParamFloat("game_time_max");
	_fadeSpeed = _options->getParamInt("fade_speed");
	_defTextColor = _options->getColor("def_text_color");
	_textTitleLivesString = _options->getParamString("text_title_lives_string");
	_textTitleTimeString = _options->getParamString("text_title_time_string");

	_cannonball = new Cannonball(_options->getParamFloat("gun_scale")
		, _cannonballTexture->getBitmapRect()
		, _options->getParamFPoint("cannon_center")
		, _options->getParamFPoint("cannonball_moveVec")
		, _topBorder 
		, _bottomBorder
		, _leftBorder
		, _rightBorder
		, _options->getParamFloat("cannonball_normalSpeed")
	);

	_buttonRestart = new Button(_options->getParamFPoint("button_restart_pos")
		, _options->getParamFloat("button_restart_scale")
		, _options->getParamString("button_restart_string")
		, _buttonUpTexture->getBitmapRect());

	_fadeBackground = Color{ _options->getColor("block_screen_color").red //затемнение фона
			, _options->getColor("block_screen_color").green
			, _options->getColor("block_screen_color").blue
			, _options->getColor("block_screen_color").alpha
	};
	_fadeMax = _options->getColor("block_screen_color").alpha;
	_blockScreen = _options->getRect("block_screen_size");

	_textEndgameTitlePos = _options->getParamFPoint("text_endgame_title_pos");
	_textEndgameResultPos = _options->getParamFPoint("text_endgame_result_pos");
	_textEndgameWinString = _options->getParamString("text_endgame_win_string");
	_textEndgameLoseString = _options->getParamString("text_endgame_lose_string");

	_panelBottomStatColor = _options->getColor("panel_bottom_stat_color");
	_panelBottomStatSize = _options->getRect("panel_bottom_stat_size");
	_panelTopStatSize = _options->getRect("panel_top_stat_size");
	_textTitleResultString = _options->getParamString("text_title_result_string");
	_textTitleSecString = _options->getParamString("text_title_sec_string");
	_targetsCountToGame = _options->getParamInt("targets_count_to_game");
	_shiftMultiplier = _options->getParamFloat("player_shift_multiplier");

	_gameTimeMax = _options->getParamFloat("game_time_max");

	_playerSpawn = _options->getParamFPoint("player_spawn");
	_playerScale = _options->getParamFloat("player_scale");

	_player = new Player(_playerScale, _playerTexture->getBitmapRect(), _playerSpawn, _options->getParamInt("player_health"));
	_cannonballPointOnPlayer.x = _playerTexture->getBitmapRect().width * _player->getScale() / 2 - _cannonball->getRadius();
	_cannonballPointOnPlayer.y = _playerTexture->getBitmapRect().height * _player->getScale();

	Render::BindFont("arial");
	SetGameStatus(GameController::GameStates::GAME);
}

void TestWidget::Draw()
{
	_gControl->setMousePos(Core::mainInput.GetMousePos());
	
	switch (_gControl->getGameState()) // Режимы игры (игра, затемнение, финальный счет)
	{
	case GameController::GameStates::GAME: // режим: игра
		_backgroundTexture->Draw();

		for (std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin(); it != _targetsBlock.end(); it++) {
			Render::device.PushMatrix();
			Render::device.MatrixTranslate((*it)->getPos());
			Render::device.MatrixScale((*it)->getScale());
			switch ((*it)->getHealth())
			{
			case 0:
				_invaderTexture_0->Draw();
				break;
			case 1:
				_invaderTexture_1->Draw();
				break;
			case 2:
				_invaderTexture_2->Draw();
				break;
			case 3:
				_invaderTexture_3->Draw();
				break;
			case 4:
				_invaderTexture_4->Draw();
				break;
			}
			Render::device.PopMatrix();
		}

		_effCont.Draw();

		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_cannonball->getPos());
		Render::device.MatrixScale(_cannonball->getScale());
		_cannonballTexture->Draw();
		Render::device.PopMatrix();

		Render::device.PushMatrix(); //игрок
		Render::device.MatrixTranslate(_player->getPos());
		Render::device.MatrixScale(_player->getScale());
		_playerTexture->Draw();
		Render::device.PopMatrix(); 
		break;

	case GameController::GameStates::TO_STOP: //игра:: затенение
		_backgroundTexture->Draw();

		_effCont.Draw();

		Render::device.SetTexturing(false);

		Render::BeginColor(Color{_fadeBackground.red, _fadeBackground.green, _fadeBackground.blue, _fade});
		Render::DrawRect(_blockScreen);
		Render::EndColor();

		Render::device.SetTexturing(true);
		if (_fade < _fadeMax) {
			_fade += _fadeSpeed; // скорость затенения
		}
		else {
			SetGameStatus(GameController::GameStates::STOP);
		}
		break;

	case GameController::GameStates::STOP: //игра: стоп
		if (_effParticleSmoke)
		{
			_effParticleSmoke->Finish();
			_effParticleSmoke = NULL;
		}
		_backgroundTexture->Draw();
		Render::device.SetTexturing(false);
		Render::BeginColor(_fadeBackground); //затенение
		Render::DrawRect(_blockScreen);
		Render::EndColor();
		Render::device.SetTexturing(true);

		Render::device.PushMatrix(); //кнопка рестарта
		Render::device.MatrixTranslate(_buttonRestart->getPos());
		Render::device.MatrixScale(_buttonRestart->getScale());
		if (_buttonRestart->getPressed()) { 
			_buttonDownTexture->Draw();
		}
		else {
			_buttonUpTexture->Draw();
		}
		Render::device.PopMatrix();

		Render::SetColor(_defTextColor);
		_lives > 0 ?
			Render::PrintString(_textEndgameTitlePos, _textEndgameWinString, 1.5f, CenterAlign, CenterAlign) :
			Render::PrintString(_textEndgameTitlePos, _textEndgameLoseString, 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_textEndgameResultPos, _textTitleResultString + " " + utils::lexical_cast(math::round(_gameTimer)) + " " + getTitlePoins(), 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_buttonRestart->getTextPos(), _buttonRestart->getText(), 1.5f, CenterAlign, CenterAlign);
		Render::ResetColor();

	default:
		break;
	}

	/*Render::device.SetTexturing(false);
	Render::BeginColor(_panelBottomStatColor);
	Render::DrawRect(_panelBottomStatSize);
	Render::DrawRect(_panelTopStatSize);
	Render::EndColor();
	Render::device.SetTexturing(true);*/
	Render::device.SetTexturing(false);
	Render::PrintString(10, _panelTopStatSize.y + _panelTopStatSize.height / 2,
		_textTitleLivesString
		+ utils::lexical_cast(_lives)
		+ " "
		+ _textTitleTimeString
		+ utils::lexical_cast(trunc(_gameTimer))
		, 1.0f, LeftAlign, CenterAlign);
	Render::device.SetTexturing(true);
	/*Render::PrintString(924 + 100 / 2, 35, "x:" + utils::lexical_cast(_gControl->getMousePos().x) + ", Y:" + utils::lexical_cast(_gControl->getMousePos().y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 65, "gameState:" + utils::lexical_cast(static_cast<int>(_gControl->getGameState())), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 95, "target count:" + utils::lexical_cast(_targetsBlock.size()), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 125, "move vec:" + utils::lexical_cast(_cannonball->getMoveVec().x) + " " + utils::lexical_cast(_cannonball->getMoveVec().y), 1.f, CenterAlign);*/
}

void TestWidget::Update(float dt)
{
	_effCont.Update(dt);

	switch (_gControl->getGameState())
	{
	case GameController::GameStates::GAME:
		_gameTimer += dt;
		_player->setPrevPosX(_player->getPos().x); //
		_player->setPosCenter(_gControl->getMousePos().x);
		_moveVecShiftX = (_player->getPos().x - _player->getPrevPosX()) * _shiftMultiplier;
		if (_cannonball->isStoped())
		{
			if (_effParticleSmoke)
			{
				_effParticleSmoke->Finish();
				_effParticleSmoke = NULL;
			}
			_cannonball->setPos(_player->getPos() + _cannonballPointOnPlayer);
			_cannonball->setMoveVec(FPoint{ _player->getPos().x - _player->getPrevPosX(), 7 });
		}
		else
		{
			if (_cannonball->Tick())
				_lives--;
			if (_effParticleSmoke)
			{
				_effParticleSmoke->SetPos(_cannonball->getCoordCenter());
			}
			// проверка на попадание по мишеням
			for (std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin(); it != _targetsBlock.end(); it++) {
				FPoint coord = (*it)->getCoordCenter();
				if (_cannonball->crossAsSphere(*(*it))) // отсекаем мишени, которые явно не рядом
				{
					_cannonball->tooClose(*(*it), 0); 
				}

			}
			
			_cannonball->tooClose(*_player, _moveVecShiftX);
		}
		
		for (std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin(); it != _targetsBlock.end(); it++) {
			(*it)->move();
		}
		int targetsToDelete = 0;
		int targetsCount = _targetsBlock.size();
		std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin();
			for (int i = 0; i < targetsCount; i++)
			{
				if ((*it)->getHealth() < 0) { //проверка на сбитие мишени
					ParticleEffectPtr eff = _effCont.AddEffect("Explosion"); //взрыв
					eff->SetPos((*it)->getCoordCenter());
					eff->Reset();

					targetsToDelete++;
					//_gamePoints += (*it)->getPoints();
					delete* it;
					std::iter_swap(it, _targetsBlock.end() - targetsToDelete); //закидываем те мишени, что сбиты в конец вектора
				}
				else {
					it++;
				}
			}
			if (targetsToDelete > 0) {
				_targetsBlock.erase(_targetsBlock.end() - targetsToDelete, _targetsBlock.end()); //очищаем от сбитых мишеней
			}
		if ((_targetsBlock.size() == 0) && (_gControl->getGameState() == GameController::GameStates::GAME)) {
			SetGameStatus(GameController::GameStates::TO_STOP);
		}
		if (_lives <= 0)
			SetGameStatus(GameController::GameStates::TO_STOP);
		break;
	}
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_buttonRestart->click(_gControl->getMousePos())) {
			SetGameStatus(GameController::GameStates::GAME);
		}
		else if (_cannonball->isStoped())
		{
			_cannonball->setStopped(false);
			_effParticleSmoke = _effCont.AddEffect("SmokeCannon");
			_effParticleSmoke->SetPos(_cannonball->getCoordCenter());
			_effParticleSmoke->Reset();
		}
	}
	for (std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin(); it != _targetsBlock.end(); it++) {
		(*it)->click(_gControl->getMousePos());
	}
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos) 
{

}

void TestWidget::MouseUp(const IPoint &mouse_pos) 
{
	_buttonRestart->noPressed();
}

void TestWidget::AcceptMessage(const Message& message) // не стал удалять с примера
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void TestWidget::KeyPressed(int keyCode) // не стал удалять с примера
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void TestWidget::CharPressed(int unicodeChar) // не стал удалять с примера
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}

void TestWidget::CreateTarget(FPoint& pos, int health, float speed, bool* toLeft)
{
	TargetsBlock* newTarget;
	newTarget = new TargetsBlock(_targetScale, _invaderTexture_0->getBitmapRect(), pos, health, speed, toLeft, _leftBorder, _rightBorder);
	_targetsBlock.push_back(newTarget);
}

void TestWidget::CreateLevel()
{
	float vPadding = _gameScreen.y - _topPadding;
	for (int i = 0; i < _levels->getParamInt("level_count"); i++)
	{
		bool* toLeft;
		toLeft = new bool(_levels->getParamBool("level_move_to_left_level_" + std::to_string(i))); //сделать уничтожение
		_levelDirection.push_back(toLeft);
		std::string level = _levels->getParamString("level_" + std::to_string(i));
		float speed = _levels->getParamFloat("level_speed_" + std::to_string(i));
		float paddingLeft = (level.length() % 2) * _targetSize.Width() / 2 * _targetScale;
		float startPos = (level.length() * (_targetSize.Width() * _targetScale + _targetHPadding)) / 2 - (_targetHPadding / 2);
		for (int targetNum = 0; targetNum < level.length(); targetNum++)
		{
			CreateTarget(FPoint{ _gameScreen.x / 2 - startPos , vPadding }, level[targetNum] - '0', speed, toLeft);
			startPos -= (_targetSize.Width() * _targetScale + _targetHPadding);
		}
		vPadding -= _targetVPadding;
	}
}

void TestWidget::SetGameStatus(const GameController::GameStates state) //смена статуса игры
{
	_gControl->setGameState(state);
	switch (state)
	{
	case GameController::GameStates::TO_STOP:
		break;

	case GameController::GameStates::GAME:
		CreateLevel();
		_lives = _options->getParamInt("max_lives_count");
		_gameTimer = 0.f;
		_buttonRestart->setActive(false);
		_fade = 0;
		_gamePoints = 0;
		_cannonball->setStopped(true);
		break;
	case GameController::GameStates::STOP:
		_buttonRestart->setActive(true);
		for (std::vector<TargetsBlock*>::iterator it = _targetsBlock.begin(); it < _targetsBlock.end(); it++) {
			delete (*it);
		}
		_targetsBlock.clear();
		for (std::vector<bool*>::iterator it = _levelDirection.begin(); it < _levelDirection.end(); it++) {
			delete (*it);
		}
		_levelDirection.clear();
		break;
	default:
		break;
	}
}

const std::string TestWidget::getTitlePoins() const
{
	std::string toReturn = "";
	std::string points = std::to_string(static_cast<int>(trunc(_gameTimer)));
	if ((points.length() == 2) && (points[0] == '1')) {
		return "секунд";
	}
	else {
		char lastSymbol = points[points.length() - 1];
		switch (lastSymbol)
		{
		case '0':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return "секунд";
			break;
		case '1':
			return "секунду";
			break;
		case '2':
		case '3':
		case '4':
			return "секунды";
			break;
		default:
			return "секунд";
			break;
		}
	}
}


