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
	_showTestButtons = false; // включить отладочные кнопки, если нужно поэксперементировать
	_cannonBackTexture = Core::resourceManager.Get<Render::Texture>("Cannon_back");
	_cannonFrontTexture = Core::resourceManager.Get<Render::Texture>("Cannon_front");
	_standTexture = Core::resourceManager.Get<Render::Texture>("Stand");
	_backgroundTexture = Core::resourceManager.Get<Render::Texture>("Background");
	_aimTexture = Core::resourceManager.Get<Render::Texture>("Aim");
	_cannonballTexture = Core::resourceManager.Get<Render::Texture>("Cannonball");
	_targetYellowTexture = Core::resourceManager.Get<Render::Texture>("Target_yellow");
	_targetRedTexture = Core::resourceManager.Get<Render::Texture>("Target_red");
	_targetBlueTexture = Core::resourceManager.Get<Render::Texture>("Target_blue");
	_buttonUpTexture = Core::resourceManager.Get<Render::Texture>("Button_up");
	_buttonDownTexture = Core::resourceManager.Get<Render::Texture>("Button_down");

	_options = new Options();
	_gControl = new GameController(GameController::GameStates::START_SCREEN, true, _options->getParamFloat("sys_timer"));
	_aim = new Aim(_options->getParamFloat("aim_scale"), _aimTexture->getBitmapRect());
	
	_cannon = new Cannon(_options->getParamFloat("cannon_angle")
		, _options->getParamFloat("gun_scale")
		, _options->getParamFPoint("cannon_stand_pos")
		, _options->getParamFPoint("cannon_rotate_point")
		, _options->getParamFPoint("cannon_center"));
	_cannonball = new Cannonball(_cannon->getScale()
		, _cannonballTexture->getBitmapRect()
		, _options->getParamFPoint("cannon_center")
		, _options->getParamFloat("cannonball_speed")
		, _options->getSplinePoints());

	_button = new Button(_options->getParamFPoint("button_create_pos")
		, _options->getParamFloat("button_create_scale")
		, _options->getParamString("button_create_string")
		, _buttonUpTexture->getBitmapRect());

	_button30Targets = new Button(_options->getParamFPoint("button_create30x_pos")
		, _options->getParamFloat("button_create_scale")
		, _options->getParamString("button_create30x_string")
		, _buttonUpTexture->getBitmapRect());

	_buttonExperiment = new Button(_options->getParamFPoint("button_experiment_pos")
		, _options->getParamFloat("button_create_scale")
		, _options->getParamString("button_experiment_string")
		, _buttonUpTexture->getBitmapRect());

	_buttonRestart = new Button(_options->getParamFPoint("button_restart_pos")
		, _options->getParamFloat("button_restart_scale")
		, _options->getParamString("button_restart_string")
		, _buttonUpTexture->getBitmapRect());

	_topBorder = _options->getParamInt("target_create_place_top");
	_bottomBorder = _options->getParamInt("target_create_place_bottom");
	_leftBorder = _options->getParamInt("target_create_place_left");
	_rightBorder = _options->getParamInt("target_create_place_right");
	_gamePoints = _options->getParamInt("game_points_default");
	_gameTimer = _options->getParamFloat("game_time_max");
	_fadeSpeed = _options->getParamInt("fade_speed");
	_defTextColor = _options->getColor("def_text_color");
	_fadeBackground = Color{ _options->getColor("block_screen_color").red //затемнение фона
			, _options->getColor("block_screen_color").green
			, _options->getColor("block_screen_color").blue
			, _options->getColor("block_screen_color").alpha
	};
	_fadeMax = _options->getColor("block_screen_color").alpha;
	_blockScreen = _options->getRect("block_screen_size");

	_textEndgameTitlePos = _options->getParamFPoint("text_endgame_title_pos");
	_textEndgamePointsPos = _options->getParamFPoint("text_endgame_points_pos");
	_textEndgameString = _options->getParamString("text_endgame_string");
	_panelBottomStatColor = _options->getColor("panel_bottom_stat_color");
	_panelBottomStatSize = _options->getRect("panel_bottom_stat_size");
	_panelTopStatSize = _options->getRect("panel_top_stat_size");
	_textTitlePointsString = _options->getParamString("text_title_points_string");
	_textTitleTimeoutString = _options->getParamString("text_title_timeout_string");
	_targetsCountToGame = _options->getParamInt("targets_count_to_game");

	_targetRedScale = _options->getParamFloat("target_red_scale");
	_targetBlueScale = _options->getParamFloat("target_blue_scale");
	_targetYellowScale = _options->getParamFloat("target_yellow_scale");

	_targetRedSpeed = _options->getParamFloat("target_red_speed");
	_targetBlueSpeed = _options->getParamFloat("target_blue_speed");
	_targetYellowSpeed = _options->getParamFloat("target_yellow_speed");

	_targetRedPoints = _options->getParamInt("target_red_points");
	_targetBluePoints = _options->getParamInt("target_blue_points");
	_targetYellowPoints = _options->getParamInt("target_yellow_points");

	_targetsCountRed = _options->getParamInt("targets_count_red");
	_targetsCountBlue = _options->getParamInt("targets_count_blue");
	_targetsCountYellow = _options->getParamInt("targets_count_yellow");

	_gameTimeMax = _options->getParamFloat("game_time_max");

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

		Render::device.PushMatrix();		// подставка под пушку
		Render::device.MatrixTranslate(_cannon->getStandPos());
		Render::device.MatrixScale(_cannon->getScale());
		_standTexture->Draw();
		Render::device.PopMatrix();

		Render::device.PushMatrix();	//задняя (фоновая часть пушки) 
		Render::device.MatrixTranslate(_cannon->getCannonCenter());
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
		Render::device.MatrixTranslate(_cannon->getCannonRotatePoint());
		Render::device.MatrixScale(_cannon->getScale());
		_cannonBackTexture->Draw();
		Render::device.PopMatrix();

		for (std::vector<Targets*>::iterator it = _targets.begin(); it != _targets.end(); it++) {
			Render::device.PushMatrix();
			Render::device.MatrixTranslate((*it)->getPos());
			Render::device.MatrixScale((*it)->getScale());
			(*it)->Draw(); // рисую из объекта, ибо ну не удобно каждый раз проверять, какая цель и какой текстурой ее рисовать
			Render::device.PopMatrix();
		}

		_effCont.Draw();

		if (!_gControl->getReadyToShot()) // рисую полет ядра
		{
			Render::device.PushMatrix();
			Render::device.MatrixTranslate(_cannonball->getPos());
			Render::device.MatrixScale(_cannonball->getScale());
			_cannonballTexture->Draw();
			Render::device.PopMatrix();
		}
		else {
			Render::device.PushMatrix(); // или рисую прицел
			Render::device.MatrixTranslate(static_cast<int>(_gControl->getMousePos().x), static_cast<int>(_gControl->getMousePos().y), 0);
			Render::device.MatrixTranslate(_aim->getCoordCenter());
			Render::device.MatrixScale(_aim->getScale());
			_aimTexture->Draw();
			Render::device.PopMatrix();
		}

		Render::device.PushMatrix(); //передняя часть пушки
		Render::device.MatrixTranslate(_cannon->getCannonCenter());
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
		Render::device.MatrixTranslate(_cannon->getCannonRotatePoint());
		Render::device.MatrixScale(_cannon->getScale());
		_cannonFrontTexture->Draw();
		Render::device.PopMatrix();

		if (_showTestButtons) // отладочные кнопки
		{
			Render::device.PushMatrix(); //кнопка создания таргета
			Render::device.MatrixTranslate(_button->getPos());
			Render::device.MatrixScale(_button->getScale());
			if (_button->getPressed()) { //кнопка нажата отпущена, рисую отсюда
				_buttonDownTexture->Draw();
			}
			else {
				_buttonUpTexture->Draw();
			}
			Render::device.PopMatrix();

			Render::device.PushMatrix(); //кнопка создания кучи таргетов
			Render::device.MatrixTranslate(_button30Targets->getPos());
			Render::device.MatrixScale(_button30Targets->getScale());
			if (_button30Targets->getPressed()) { 
				_buttonDownTexture->Draw();
			}
			else {
				_buttonUpTexture->Draw();
			}
			Render::device.PopMatrix();

			Render::device.PushMatrix(); //кнопка для эксперимента со столкновениями
			Render::device.MatrixTranslate(_buttonExperiment->getPos());
			Render::device.MatrixScale(_buttonExperiment->getScale());
			if (_buttonExperiment->getPressed()) { 
				_buttonDownTexture->Draw();
			}
			else {
				_buttonUpTexture->Draw();
			}
			Render::device.PopMatrix();


			Render::SetColor(_defTextColor); //текст на кнопках
			Render::PrintString(_button->getTextPos(), _button->getText(), 1.5f, CenterAlign, CenterAlign);
			Render::PrintString(_button30Targets->getTextPos(), _button30Targets->getText(), 1.5f, CenterAlign, CenterAlign);
			Render::PrintString(_buttonExperiment->getTextPos(), _buttonExperiment->getText(), 1.5f, CenterAlign, CenterAlign);
			Render::ResetColor();
		}
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
		Render::PrintString(_textEndgameTitlePos, _textEndgameString, 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_textEndgamePointsPos, utils::lexical_cast(_gamePoints) + " " + getTitlePoins(), 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_buttonRestart->getTextPos(), _buttonRestart->getText(), 1.5f, CenterAlign, CenterAlign);
		Render::ResetColor();

	default:
		break;
	}

	Render::device.SetTexturing(false);
	Render::BeginColor(_panelBottomStatColor);
	Render::DrawRect(_panelBottomStatSize);
	Render::DrawRect(_panelTopStatSize);
	Render::EndColor();
	Render::device.SetTexturing(true);
	
	Render::PrintString(10, _panelTopStatSize.y + _panelTopStatSize.height / 2,
		_textTitlePointsString
		+ utils::lexical_cast(_gamePoints)
		+ " "
		+ _textTitleTimeoutString
		+ utils::lexical_cast(math::round(_gameTimer))
		, 1.0f, LeftAlign, CenterAlign);
	Render::PrintString(924 + 100 / 2, 35, "x:" + utils::lexical_cast(_gControl->getMousePos().x) + ", Y:" + utils::lexical_cast(_gControl->getMousePos().y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 65, "gameState:" + utils::lexical_cast(static_cast<int>(_gControl->getGameState())), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 95, "target count:" + utils::lexical_cast(_targets.size()), 1.f, CenterAlign);
}

void TestWidget::Update(float dt)
{
	_effCont.Update(dt);

	switch (_gControl->getGameState())
	{
	case GameController::GameStates::GAME:
		_gameTimer -= dt;
		if (!_gControl->getReadyToShot()) {
			_cannonball->updPosition(_gControl->getTimer()); //полет ядра
			_effParticleSmoke->SetPos(_cannonball->getCoordCenter());
			if (_cannonball->getPos().y < 0) { //прилетело - очищаю
				_gControl->setReadyToShot(true);
				_cannonball->splineClear();
				if (_effParticleSmoke)
				{
					_effParticleSmoke->SetPos(FPoint{ -100, -100 }); //чтобы завершился за пределами экрана
					_effParticleSmoke->Finish();
					_effParticleSmoke = NULL;
				}
			}
			_gControl->setTimer(_gControl->getTimer() + dt * _cannonball->getFlightTime());
			while (_gControl->getTimer() > 2 * math::PI) 
			{
				_gControl->setTimer(_gControl->getTimer() - 2 * math::PI);
			}
		}
		_cannon->setAngle(atan2(_cannon->getCannonCenter().y - _gControl->getMousePos().y, _cannon->getCannonCenter().x - _gControl->getMousePos().x) / math::PI * 180 + 90);
		if (!_gControl->getReadyToShot()) { //если ядро кого-то может сбить
			int targetsToDelete = 0;
			int targetsCount = _targets.size();
			std::vector<Targets*>::iterator it = _targets.begin();
			for (int i = 0; i < targetsCount; i++)
			{
				if ((*it)->isCrossing(_cannonball->getPos(), _cannonball->getRadius())) { //проверка на сбитие мишени
					ParticleEffectPtr eff = _effCont.AddEffect("Explosion"); //взрыв
					eff->SetPos((*it)->getCoordCenter());
					eff->Reset();

					targetsToDelete++;
					_gamePoints += (*it)->getPoints();
					delete* it;
					std::iter_swap(it, _targets.end() - targetsToDelete); //закидываем те мишени, что сбиты в конец вектора
				}
				else {
					it++;
				}
			}
			if (targetsToDelete > 0) {
				_targets.erase(_targets.end() - targetsToDelete, _targets.end()); //очищаем от сбитых мишеней
			}
		}

		for (std::vector<Targets*>::iterator it_hunt = _targets.begin(); it_hunt != _targets.end(); it_hunt++)
		{
			(*it_hunt)->Tick();
			for (std::vector<Targets*>::iterator it_vict = _targets.begin(); it_vict != _targets.end(); it_vict++)
			{
				if ((it_hunt != it_vict) &&
					(LocalFunctions::pointToPointRange((*it_hunt)->getCoordCenter(), (*it_vict)->getCoordCenter()) <= ((*it_hunt)->getRadius() + (*it_vict)->getRadius()))
					) {
					(*it_hunt)->tooClose(*(*it_vict)); // столкновение с объектами
				}
			}
		}
		if (((_gameTimer <= 0.f) || (_targets.size() == 0)) & (_gControl->getGameState() == GameController::GameStates::GAME)) {
			_gameTimer = 0.f;
			SetGameStatus(GameController::GameStates::TO_STOP);
		}
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
		else if (_gControl->getReadyToShot()) // можно стрелять
		{
			_gControl->setReadyToShot(false);
			_cannonball->setFlightTime( 1 / LocalFunctions::pointToPointRange(_gControl->getMousePos(), _cannon->getCannonCenter()) * _cannonball->getSpeed() );
			_cannonball->setSpline(_cannon->getCannonCenter(), _gControl->getMousePos());
			_gControl->setTimer(0);

			_effParticleSmoke = _effCont.AddEffect("SmokeCannon");
			_effParticleSmoke->SetPos(_cannonball->getPos());
			_effParticleSmoke->Reset();
		}
		if (_showTestButtons) {
			TestButtonsClick();
		}
	}
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos) 
{

}

void TestWidget::MouseUp(const IPoint &mouse_pos) 
{
	_button->noPressed();
	_button30Targets->noPressed();
	_buttonExperiment->noPressed();
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

void TestWidget::CreateTarget()
{
	int numTarget = math::random(2);
	Targets* newTarget;
	FPoint randPos({ static_cast<float>(math::random(_rightBorder - _leftBorder) + _leftBorder), static_cast<float>(math::random(_topBorder - _bottomBorder) + _bottomBorder) });

	switch (numTarget) 
	{
	case(0):
		newTarget = new Targets(_targetYellowScale
			, _targetYellowTexture->getBitmapRect()
			, randPos
			, _targetYellowTexture
			, LocalFunctions::randomVec(_targetYellowSpeed)
			, _targetYellowSpeed
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder
			, _targetYellowPoints
		);
		break;
	case(1):
		newTarget = new Targets(_targetRedScale
			, _targetRedTexture->getBitmapRect()
			, randPos
			, _targetRedTexture
			, LocalFunctions::randomVec(_targetRedSpeed)
			, _targetRedSpeed
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder
			, _targetRedPoints
		);
		break;
	case(2):
		newTarget = new Targets(_targetBlueScale
			, _targetBlueTexture->getBitmapRect()
			, randPos
			, _targetBlueTexture
			, LocalFunctions::randomVec(_targetBlueSpeed)
			, _targetBlueSpeed
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder
			, _targetBluePoints
		);
		break;
	default:
		newTarget = new Targets(_targetYellowScale
			, _targetYellowTexture->getBitmapRect()
			, randPos
			, _targetYellowTexture
			, LocalFunctions::randomVec(_targetYellowSpeed)
			, _targetYellowSpeed
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder
			, _targetYellowPoints
		);
		break;
	}
	_targets.push_back(newTarget);
}

void TestWidget::CreateTarget(FPoint& pos, FPoint& moveVec) // мишень в конкретном месте и с нужным направлением движения
{
	Targets* newTarget;
	newTarget = new Targets(_targetBlueScale
		, _targetBlueTexture->getBitmapRect()
		, pos
		, _targetBlueTexture
		, moveVec
		, _targetBlueSpeed
		, _topBorder
		, _bottomBorder
		, _leftBorder
		, _rightBorder
		, _targetBluePoints
	);
	_targets.push_back(newTarget);
}

void TestWidget::CreateSomeTarget(int count)
{
	for (int i = 0; i < count; i++) {
		CreateTarget();
	}
}

void TestWidget::CreateColorTarget(const char color, const int count) //создать конкрнетные мишени
{
	for (int i = 0; i < count; i++)
	{
		Targets* newTarget;
		FPoint randPos({ static_cast<float>(math::random(_rightBorder - _leftBorder) + _leftBorder), static_cast<float>(math::random(_topBorder - _bottomBorder) + _bottomBorder) });
		switch (color) 
		{
		case('y'):
			newTarget = new Targets(_targetYellowScale
				, _targetYellowTexture->getBitmapRect()
				, randPos
				, _targetYellowTexture
				, LocalFunctions::randomVec(_targetYellowSpeed)
				, _targetYellowSpeed 
				, _topBorder
				, _bottomBorder
				, _leftBorder
				, _rightBorder
				, _targetYellowPoints
			);
			break;
		case('r'):
			newTarget = new Targets(_targetRedScale
				, _targetRedTexture->getBitmapRect()
				, randPos
				, _targetRedTexture
				, LocalFunctions::randomVec(_targetRedSpeed)
				, _targetRedSpeed
				, _topBorder
				, _bottomBorder
				, _leftBorder
				, _rightBorder
				, _targetRedPoints
			);
			break;
		case('b'):
			newTarget = new Targets(_targetBlueScale
				, _targetBlueTexture->getBitmapRect()
				, randPos
				, _targetBlueTexture
				, LocalFunctions::randomVec(_targetBlueSpeed)
				, _targetBlueSpeed
				, _topBorder
				, _bottomBorder
				, _leftBorder
				, _rightBorder
				, _targetBluePoints
			);
			break;
		default:
			newTarget = new Targets(_targetYellowScale 
				, _targetYellowTexture->getBitmapRect()
				, randPos
				, _targetYellowTexture
				, LocalFunctions::randomVec(_targetYellowSpeed )
				, _targetYellowSpeed 
				, _topBorder
				, _bottomBorder
				, _leftBorder
				, _rightBorder
				, _targetYellowPoints
			);
			break;
		}
		_targets.push_back(newTarget);
	}
}

void TestWidget::SetGameStatus(const GameController::GameStates state) //смена статуса игры
{
	_gControl->setGameState(state);
	switch (state)
	{
	case GameController::GameStates::TO_STOP:
		_button->setActive(false);
		_button30Targets->setActive(false);
		_buttonExperiment->setActive(false);
		break;

	case GameController::GameStates::GAME:
		CreateColorTarget('b', _targetsCountBlue);
		CreateColorTarget('y', _targetsCountYellow);
		CreateColorTarget('r', _targetsCountRed);
		if (_showTestButtons)
		{
			_button->setActive(true);
			_button30Targets->setActive(true);
			_buttonExperiment->setActive(true);
		}
		_buttonRestart->setActive(false);
		_fade = 0;
		_gamePoints = 0;
		_cannonball->splineClear();
		_gControl->setReadyToShot(true);
		_gameTimer = _gameTimeMax;
		break;
	case GameController::GameStates::STOP:
		_buttonRestart->setActive(true);
		for (std::vector<Targets*>::iterator it = _targets.begin(); it < _targets.end(); it++) {
			delete (*it);
		}
		_targets.clear();
		break;
	default:
		break;
	}
}

const std::string TestWidget::getTitlePoins() const
{
	std::string toReturn = "";
	std::string points = std::to_string(_gamePoints);
	if ((points.length() == 2) & (points[0] == '1')) {
		return "очков";
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
			return "очков";
			break;
		case '1':
			return "очко";
			break;
		case '2':
		case '3':
		case '4':
			return "очка";
			break;
		default:
			return "очков";
			break;
		}
	}
}

void TestWidget::TestButtonsClick()
{
	if (_button->click(_gControl->getMousePos())) {
		CreateTarget();
	}
	else if (_button30Targets->click(_gControl->getMousePos())) {
		CreateSomeTarget(_targetsCountToGame);
	}
	else if (_buttonExperiment->click(_gControl->getMousePos())) {
		CreateTarget(FPoint{ 300.f, 400.f }, FPoint{ 1.f, 1.f });
		CreateTarget(FPoint{ 500.f, 400.f }, FPoint{ -1.f, 1.f });
		CreateTarget(FPoint{ 300.f, 600.f }, FPoint{ 1.f, -1.f });
		CreateTarget(FPoint{ 500.f, 600.f }, FPoint{ -1.f, -1.f });
	}
}
