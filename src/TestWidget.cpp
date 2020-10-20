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
	//, _curTex(0)
	, _eff(NULL)
{
	Init();
}

void TestWidget::Init()
{
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

	_topBorder = _options->getParamInt("target_create_place_top");
	_bottomBorder = _options->getParamInt("target_create_place_bottom");
	_leftBorder = _options->getParamInt("target_create_place_left");
	_rightBorder = _options->getParamInt("target_create_place_right");

	Render::BindFont("arial");


	//гружу текстуры
	
}

void TestWidget::Draw()
{
	_gControl->setMousePos(Core::mainInput.GetMousePos());
	
	switch (_gControl->getGameState()) // Будущие режимы игры (заставка, игра, финальный счет)
	{
	case GameController::GameStates::START_SCREEN: // режим: игра
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

		for (std::list<Targets>::iterator it = _targets.begin(); it != _targets.end(); it++) {
			Render::device.PushMatrix();
			Render::device.MatrixTranslate(it->getPos());
			Render::device.MatrixScale(it->getScale());
			it->Draw(); // рисую из объекта, ибо ну не удобно каждый раз проверять, какая цель и какой текстурой ее рисовать
			Render::device.PopMatrix();
		}

		if (!_gControl->getReadyToShot())
		{
			_cannonball->updPosition(_gControl->getTimer()); //ядро
			Render::device.PushMatrix();
			Render::device.MatrixTranslate(_cannonball->getPosition());
			Render::device.MatrixScale(_cannonball->getScale());
			_cannonballTexture->Draw();
			Render::device.PopMatrix();
		}

		Render::device.PushMatrix(); //передняя часть пушки
		Render::device.MatrixTranslate(_cannon->getCannonCenter());
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
		Render::device.MatrixTranslate(_cannon->getCannonRotatePoint());
		Render::device.MatrixScale(_cannon->getScale());
		_cannonFrontTexture->Draw();
		Render::device.PopMatrix();

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
		if (_button30Targets->getPressed()) { //кнопка нажата отпущена, рисую отсюда
			_buttonDownTexture->Draw();
		}
		else {
			_buttonUpTexture->Draw();
		}
		Render::device.PopMatrix();

		Render::device.PushMatrix(); //кнопка для эксперимента
		Render::device.MatrixTranslate(_buttonExperiment->getPos());
		Render::device.MatrixScale(_buttonExperiment->getScale());
		if (_buttonExperiment->getPressed()) { //кнопка нажата отпущена, рисую отсюда
			_buttonDownTexture->Draw();
		}
		else {
			_buttonUpTexture->Draw();
		}
		Render::device.PopMatrix();
		

		Render::SetColor(Color(0, 0, 0, 255));
		Render::PrintString(_button->getTextPos(), _button->getText(), 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_button30Targets->getTextPos(), _button30Targets->getText(), 1.5f, CenterAlign, CenterAlign);
		Render::PrintString(_buttonExperiment->getTextPos(), _buttonExperiment->getText(), 1.5f, CenterAlign, CenterAlign);
		Render::ResetColor();


		Render::device.PushMatrix(); //прицел
		Render::device.MatrixTranslate(static_cast<int>(_gControl->getMousePos().x), static_cast<int>(_gControl->getMousePos().y), 0);
		Render::device.MatrixTranslate(_aim->getCoordCenter());
		Render::device.MatrixScale(_aim->getScale());
		_aimTexture->Draw();
		Render::device.PopMatrix();

		break;
		
	}
	
	
	//
	// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
	// можно было восстановить это преобразование вызовом PopMatrix.
	
	
	//
	// Изменяем текущее преобразование координат, перемещая центр координат в позицию мыши
	// и поворачивая координаты относительно этого центра вокруг оси z на угол _angle.
	//
	
	/*Render::device.PushMatrix();
	Render::device.MatrixTranslate(static_cast<int>(_gControl->getMousePos().x), static_cast<int>(_gControl->getMousePos().y), 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());

	if (!_curTex)
	{
		//
		// Метод Texture::Draw() выводит квадратный спрайт с размерами текстуры
		// в центре координат (0, 0). Центр координат и преобразование координат вершин
		// спрайта устанавливаются с применением текущего преобразования.
		//
		// При вызове метода Texture::Draw() вызывать Texture::Bind() необязательно.
		//
		// _tex1->Draw();
	}
	else
	{
		// IRect texRect = _tex2->getBitmapRect();

		//
		// При отрисовке текстуры можно вручную задавать UV координаты той части текстуры,
		// которая будет натянута на вершины спрайта. UV координаты должны быть нормализованы,
		// т.е., вне зависимости от размера текстуры в текселях, размер любой текстуры
		// равен 1 (UV координаты задаются в диапазоне 0..1, хотя ничто не мешает задать их
		// больше единицы, при этом в случае установленной адресации текстуры REPEAT, текстура
		// будет размножена по этой стороне соответствующее количество раз).
		//

		// FRect rect(texRect);
		// FRect uv(0, 1, 0, 1);

		// _tex2->TranslateUV(rect, uv);

		// Render::device.MatrixScale(_scale);
		//Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);

		//
		// Привязываем текстуру.
		//
		//_tex2->Bind();
		
		//
		// Метод DrawQuad() выводит в графическое устройство квадратный спрайт, состоящий их двух
		// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
		// если разрешено текстурирование.
		//
		// Перед вызовом DrawQuad() должен быть вызов Texture::Bind() либо SetTexturing(false),
		// иначе визуальный результат будет непредсказуемым.
		//
		//Render::DrawQuad(rect, uv);
	}


	
	//
	// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
	//
	Render::device.PopMatrix();*/
	
	//
	// Получаем текущие координаты объекта, двигающегося по сплайну
	//
	

	//
	// И рисуем объект в этих координатах
	//
	

	//
	// Этот вызов отключает текстурирование при отрисовке.
	//
	Render::device.SetTexturing(false);
	
	//
	// Метод BeginColor() проталкивает в стек текущий цвет вершин и устанавливает новый.
	//
	Render::BeginColor(Color(255, 128, 0, 255));
	for (std::list<Targets>::iterator it_hunt = _targets.begin(); it_hunt != _targets.end(); it_hunt++)
	{
		DrawCross(it_hunt->getCoordCenter());
	}
	//DrawCross(_button->getTextPos());
	//
	// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
	// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
	// если разрешено текстурирование.
	//
	// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
	// иначе визуальный результат будет непредсказуемым.
	//
	Render::DrawRect(924, 0, 100, 100);
	Render::EndColor();
	
	//
	// Опять включаем текстурирование.
	//
	Render::device.SetTexturing(true);
	
	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();
	
	//_button->printText();
	
	
	Render::PrintString(924 + 100 / 2, 35, "x:" + utils::lexical_cast(_gControl->getMousePos().x) + ", Y:" + utils::lexical_cast(_gControl->getMousePos().y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 65, "gameState:" + utils::lexical_cast(static_cast<int>(_gControl->getGameState())), 1.f, CenterAlign);
	//Render::PrintString(924 + 100 / 2, 95, "target angle:" + utils::lexical_cast(_targetAngle), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 125, "target count:" + utils::lexical_cast(_targets.size()), 1.f, CenterAlign);
}

void TestWidget::Update(float dt)
{
	//_cannonball_pos = _cannonball->getPos();
	//
	// Обновим контейнер с эффектами
	//
	_effCont.Update(dt);

	//
	// dt - значение времени в секундах, прошедшее от предыдущего кадра.
	// Оно может принимать разные значения, в зависимости от производительности системы
	// и сложности сцены.
	//
	// Для того, чтобы наша анимация зависела только от времени, и не зависела от
	// производительности системы, мы должны рассчитывать её от этого значения.
	//
	// Увеличиваем наш таймер с удвоенной скоростью.
	//
	_gControl->changeTimer() += dt * _cannonball->getFlightTime();
	
	//
	// Зацикливаем таймер в диапазоне (0, 2п).
	// Это нужно делать для предотвращения получения некорректных значений,
	// если вдруг переполнится разрядная сетка (float переполнился) или задержка
	// от предыдущего кадра была слишкой большой (система тормози-и-ит).
	//
	// Диапазон значений выбран равным (0, 2п), потому что мы используем это значение
	// для расчёта синуса, и большие значения будут просто периодически повторять результат.
	//
	while (_gControl->getTimer() > 2 * math::PI)
	{
		_gControl->changeTimer() -= 2 * math::PI;
		_gControl->setReadyToShot(true);
		_cannonball->splineClear(); // зря вызываю каждый раз, потом буду вызывать в конце пути ядра
	}
	
	//
	// Анимирование параметра масштабирования в зависимости от таймера.
	//
		
	//переделал хранилище целей из вектор в список, ибо, как я почитал, объекты не с краев лучше удалять именно из списка.
	_cannon->setAngle( atan2(_cannon->getCannonCenter().y - _gControl->getMousePos().y, _cannon->getCannonCenter().x - _gControl->getMousePos().x) / math::PI * 180 + 90 );
	if (!_gControl->getReadyToShot()) {
		for (std::list<Targets>::iterator it = _targets.begin(); it != _targets.end();)
		{
			if (it->isCrossing(_cannonball->getPosition(), _cannonball->getRadius())) {
				it = _targets.erase(it);
			}
			else {
				it++;
			}
		}
	}

	for (std::list<Targets>::iterator it_hunt = _targets.begin(); it_hunt != _targets.end(); it_hunt++)
	{
		it_hunt->Tick();
		for (std::list<Targets>::iterator it_vict = _targets.begin(); it_vict != _targets.end(); it_vict++)
		{
			if (it_hunt != it_vict) { 
				//можно оба условия засунуть в одну проверку, но я так понимаю, 
				//что так будет быстрее, типа отсекает по сравнению, один это объект, или нет
				if (LocalFunctions::pointToPointRange(it_hunt->getCoordCenter(), it_vict->getCoordCenter()) <= (it_hunt->getRadius() + it_vict->getRadius())) {
					it_hunt->tooClose(*it_vict);
				}
			}
		}
	}
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseRightButton())
	{
		// При нажатии на правую кнопку мыши, создаём эффект шлейфа за мышкой.
		//
		/*_eff = _effCont.AddEffect("Iskra");
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
		_eff->Reset();*/
		
		//
		// И изменяем угол наклона текстуры.
		//
	}
	else
	{
		if (_button->click(_gControl->getMousePos())) { 
			CreateTarget();
		}
		else if (_button30Targets->click(_gControl->getMousePos())) {
			for (int i = 0; i < 30; i++) {
				CreateTarget();
			}
		}
		else if (_buttonExperiment->click(_gControl->getMousePos())) {
			CreateTarget(FPoint{ 300.f, 400.f }, FPoint{ 1.f, 1.f });
			CreateTarget(FPoint{ 500.f, 400.f }, FPoint{ -1.f, 1.f });
			CreateTarget(FPoint{ 300.f, 600.f }, FPoint{ 1.f, -1.f });
			CreateTarget(FPoint{ 500.f, 600.f }, FPoint{ -1.f, -1.f });
		}
		else if (_gControl->getReadyToShot())
		{
			_gControl->setReadyToShot(false);
			_cannonball->setFlightTime( 1 / LocalFunctions::pointToPointRange(_gControl->getMousePos(), _cannon->getCannonCenter()) * _cannonball->getSpeed() );
			_cannonball->setSpline(_cannon->getCannonCenter(), _gControl->getMousePos());
			_gControl->setTimer(0);
		}
		//
		//
		// При нажатии на левую кнопку мыши, создаём временный эффект, который завершится сам.
		//
		//_gControl->setGameState(static_cast<GameController::GameStates>(static_cast<int>(_gControl->getGameState()) + 1));
		/*ParticleEffectPtr eff = _effCont.AddEffect("FindItem2");
		eff->posX = _mousePos.x + 0.f;
		eff->posY = _mousePos.y + 0.f;
		eff->Reset();*/

		//
		// Изменяем значение с 0 на 1 и наоборот.
		//
		//_curTex = 1 - _curTex;
	}
	return false;
}

void TestWidget::MouseMove(const IPoint &mouse_pos) // можно не смотреть, это было в демке.
{
	if (_eff)
	{
		//
		// Если эффект создан, то перемещаем его в позицию мыши.
		//
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
	}
}

void TestWidget::MouseUp(const IPoint &mouse_pos) // можно не смотреть, это было в демке.
{
	_button->noPressed();
	_button30Targets->noPressed();
	_buttonExperiment->noPressed();
	if (_eff)
	{
		//
		// Если эффект создан, то при отпускании мыши завершаем его.
		//
		_eff->Finish();
		_eff = NULL;
	}
}

void TestWidget::AcceptMessage(const Message& message) // можно не смотреть, это было в демке.
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void TestWidget::KeyPressed(int keyCode) // можно не смотреть, это было в демке.
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
		// _cannon->getAngle() -= 25;
	}
}

void TestWidget::CharPressed(int unicodeChar) // можно не смотреть, это было в демке.
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

	switch (numTarget) //норм ли такой вид, через свитч-кейс и рандом?
	{
	case(0):
		newTarget = new Targets(_options->getParamFloat("target_yellow_scale")
			, _targetYellowTexture->getBitmapRect()
			, randPos
			, _targetYellowTexture
			, LocalFunctions::randomVec(_options->getParamFloat("target_yellow_speed"))
			, _options->getParamFloat("target_yellow_speed")
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder);
		break;
	case(1):
		newTarget = new Targets(_options->getParamFloat("target_red_scale")
			, _targetRedTexture->getBitmapRect()
			, randPos
			, _targetRedTexture
			, LocalFunctions::randomVec(_options->getParamFloat("target_red_speed"))
			, _options->getParamFloat("target_red_speed")
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder);
		break;
	case(2):
		newTarget = new Targets(_options->getParamFloat("target_blue_scale")
			, _targetBlueTexture->getBitmapRect()
			, randPos
			, _targetBlueTexture
			, LocalFunctions::randomVec(_options->getParamFloat("target_blue_speed"))
			, _options->getParamFloat("target_blue_speed")
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder);
		break;
	default:
		newTarget = new Targets(_options->getParamFloat("target_yellow_scale")
			, _targetYellowTexture->getBitmapRect()
			, randPos
			, _targetYellowTexture
			, LocalFunctions::randomVec(_options->getParamFloat("target_yellow_speed"))
			, _options->getParamFloat("target_yellow_speed")
			, _topBorder
			, _bottomBorder
			, _leftBorder
			, _rightBorder);
		break;
	}
	_targets.push_back(*newTarget);
}

void TestWidget::CreateTarget(FPoint& pos, FPoint& moveVec)
{
	Targets* newTarget;
	newTarget = new Targets(_options->getParamFloat("target_blue_scale")
		, _targetBlueTexture->getBitmapRect()
		, pos
		, _targetBlueTexture
		, moveVec
		, _options->getParamFloat("target_blue_speed")
		, _topBorder
		, _bottomBorder
		, _leftBorder
		, _rightBorder);
	_targets.push_back(*newTarget);
}
