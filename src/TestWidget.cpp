#include "stdafx.h"
#include "TestWidget.h"

void DrawCross(int x, int y, std::string title)
{
	Render::DrawLine(math::Vector3(x - 10, y, 1), math::Vector3(x + 10, y, 1));
	Render::DrawLine(math::Vector3(x, y - 10, 1), math::Vector3(x, y + 10, 1));
}

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _timer(0)
	, _eff(NULL)
{
	Init();
}

void TestWidget::Init()
{
	_options = new Options();
	_gControl = new GameController(GameController::GameStates::START_SCREEN, true, _options->getParam("gun_scale"));
	_cannon = new Cannon(90.0f);
	_cannonball = new Cannonball({ 200, 200 });
	_cannonBack = Core::resourceManager.Get<Render::Texture>("Cannon_back");
	_cannonFront = Core::resourceManager.Get<Render::Texture>("Cannon_front");
	_stand = Core::resourceManager.Get<Render::Texture>("Stand");
	_background = Core::resourceManager.Get<Render::Texture>("Background");
	_aim = Core::resourceManager.Get<Render::Texture>("Aim");
	_point = Core::resourceManager.Get<Render::Texture>("TestPoint");
	_cannonbalPic = Core::resourceManager.Get<Render::Texture>("Cannonball");
}

void TestWidget::Draw()
{
	_gControl->setMousePos(Core::mainInput.GetMousePos());
	_background->Draw();

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_cannonCenter.x, _cannonCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
	Render::device.MatrixTranslate(_cannonRotatePoint.x, _cannonRotatePoint.y, 0);
	Render::device.MatrixScale(_gControl->getWeaponScale());
	_cannonBack->Draw();
	Render::device.PopMatrix();

	switch (_gControl->getGameState())
	{
	case GameController::GameStates::START_SCREEN:
		Render::device.PushMatrix();
		Render::device.MatrixTranslate((float)_gControl->getMousePos().x, (float)_gControl->getMousePos().y, 0);
		IRect texRect = _aim->getBitmapRect();
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);
		_aim->Draw();
		Render::device.PopMatrix();

		break;
		
	}
	if (!_gControl->getReadyToShot())
	{
		FPoint currentPosition = spline.getGlobalFrame(math::clamp(0.0f, 1.0f, _timer / 6.0f));
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(currentPosition.x + _cannonballCenter.x, currentPosition.y + _cannonballCenter.y, 0);
		Render::device.MatrixScale(_gControl->getWeaponScale());
		//Render::device.MatrixTranslate(currentPosition, 0);
		_cannonbalPic->Draw();
		Render::device.PopMatrix();
	}
	
	//
	// Получаем текущее положение курсора мыши.
	//

	

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_standPos.x, _standPos.y, 0);
	Render::device.MatrixScale(_gControl->getWeaponScale());
	_stand->Draw();
	Render::device.PopMatrix();

	Render::device.PushMatrix();
	Render::device.MatrixTranslate(_cannonCenter.x, _cannonCenter.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
	Render::device.MatrixTranslate(_cannonRotatePoint.x, _cannonRotatePoint.y, 0);
	Render::device.MatrixScale(_gControl->getWeaponScale());
	_cannonFront->Draw();
	Render::device.PopMatrix();

	//
	// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
	// можно было восстановить это преобразование вызовом PopMatrix.
	
	
	//
	// Изменяем текущее преобразование координат, перемещая центр координат в позицию мыши
	// и поворачивая координаты относительно этого центра вокруг оси z на угол _angle.
	//
	
	Render::device.PushMatrix();
	Render::device.MatrixTranslate((float)_gControl->getMousePos().x, (float)_gControl->getMousePos().y, 0);
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
	Render::device.PopMatrix();
	
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
	
	//
	// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
	// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
	// если разрешено текстурирование.
	//
	// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
	// иначе визуальный результат будет непредсказуемым.
	//
	Render::DrawRect(924, 0, 100, 100);

	/*DrawCross(100, 100);
	DrawCross(150, 300);
	DrawCross(500, 300);
	DrawCross(630, 450);
	DrawCross(600, 550);*/
	//
	// Метод EndColor() снимает со стека текущий цвет вершин, восстанавливая прежний.

	/*
	spline.addKey(0.0f, FPoint(100.0f, 100.0f));
	spline.addKey(0.25f, FPoint(150.0f, 300.0f));
	spline.addKey(0.5f, FPoint(500.0f, 300.0f));
	spline.addKey(0.75f, FPoint(630.0f, 450.0f));
	spline.addKey(1.0f, FPoint(600.0f, 550.0f));
	*/
	//
	Render::EndColor();
	
	//
	// Опять включаем текстурирование.
	//
	Render::device.SetTexturing(true);

	/////////////////////////////////////////
	/*Render::device.SetTexturing(false);
	Render::BeginColor(Color(0, 0, 0, 255));
	DrawCross(_cannonCenter.x, _cannonCenter.y, "1");
	DrawCross(_mouse_pos.x, _mouse_pos.y, "2");
	DrawCross(_mouse_pos.x + 2 * (_mouse_pos.x - _cannonCenter.x), _mouse_pos.y, "3");
	DrawCross(_mouse_pos.x + (_mouse_pos.x - _cannonCenter.x), _mouse_pos.y, "4");
	DrawCross(_mouse_pos.x + (_mouse_pos.x - _cannonCenter.x), _mouse_pos.y + 0.5 * (_mouse_pos.y - _cannonCenter.y), "5");
	Render::EndColor();
	Render::BeginColor(Color(255, 0, 0, 255));
	DrawCross(_mouse_pos.x + 0.1 * (_mouse_pos.x - _cannonCenter.x), _mouse_pos.y + 0.1 * (_mouse_pos.y - _cannonCenter.y), "6");
	DrawCross(_cannonCenter.x + 1.75 * (_mouse_pos.x + (_mouse_pos.x - _cannonCenter.x) - _cannonCenter.x), _cannonCenter.y, "7");
	Render::EndColor();
	Render::device.SetTexturing(true);*/
	/////////////////////////////////////////
	
	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, "x:" + utils::lexical_cast(_gControl->getMousePos().x) + ", Y:" + utils::lexical_cast(_gControl->getMousePos().y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 65, "gameState:" + utils::lexical_cast(static_cast<int>(_gControl->getGameState())), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 95, "options:" + utils::lexical_cast(_options->getParam("scale")), 1.f, CenterAlign);
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
	_timer += dt * _cannonTimer;
	
	//
	// Зацикливаем таймер в диапазоне (0, 2п).
	// Это нужно делать для предотвращения получения некорректных значений,
	// если вдруг переполнится разрядная сетка (float переполнился) или задержка
	// от предыдущего кадра была слишкой большой (система тормози-и-ит).
	//
	// Диапазон значений выбран равным (0, 2п), потому что мы используем это значение
	// для расчёта синуса, и большие значения будут просто периодически повторять результат.
	//
	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
		_gControl->setReadyToShot(true);
		spline.Clear();
	}
		
	
	//
	// Анимирование параметра масштабирования в зависимости от таймера.
	//
	/*
	_scale = 0.8f + 0.25f * sinf(_timer);
	if (_angle >= 360) {
		_angle -= 360;
	}*/
	
	_cannon->getAngle() = atan2(_cannonCenter.y - _gControl->getMousePos().y, _cannonCenter.x - _gControl->getMousePos().x) / math::PI * 180 + 90;
	//_angle = math::GetXYVectorAngle({ (float)_cannonCenter.x, (float)_cannonCenter.y, 0.0f } , { (float)_mouse_pos.x, (float)_mouse_pos.y, 0.0f });
	//_angle = (_angle < 0) ? _angle + 360 : _angle;
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
		/*
		_angle += 25;
		while (_angle > 360)
		{
			_angle -= 360;
		}*/
	}
	else
	{
		if (_gControl->getReadyToShot())
		{
			logStr = logStr + "ready ";
			_gControl->setReadyToShot(false);
			bool stat = _gControl->getReadyToShot();
			_shotLenth = math::sqrt(math::abs(math::sqr(_gControl->getMousePos().x - _cannonCenter.x) + math::sqr(_gControl->getMousePos().y - _cannonCenter.y)));
			_cannonTimer = 4 /_shotLenth * 500;
			
			spline.addKey(0.0f, _cannonCenter);
			spline.addKey(0.3f, _gControl->getMousePos());
			spline.addKey(0.5f, { (float)(_gControl->getMousePos().x + (_gControl->getMousePos().x - _cannonCenter.x)), (float)(_gControl->getMousePos().y + 0.3 * (_gControl->getMousePos().y - _cannonCenter.y)) });
			spline.addKey(0.7f, { (float)(_gControl->getMousePos().x + 2 * (_gControl->getMousePos().x - _cannonCenter.x)), (float)(_gControl->getMousePos().y) });
			spline.addKey(1.0f, { (float)(_cannonCenter.x + 1.75 * (_gControl->getMousePos().x + (_gControl->getMousePos().x - _cannonCenter.x) - _cannonCenter.x)), (float)(-30) });
			spline.CalculateGradient();
			_timer = 0;
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

void TestWidget::MouseMove(const IPoint &mouse_pos)
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

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
	if (_eff)
	{
		//
		// Если эффект создан, то при отпускании мыши завершаем его.
		//
		_eff->Finish();
		_eff = NULL;
	}
}

void TestWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//

	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void TestWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//

	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
		// _cannon->getAngle() -= 25;
	}
	/*
	if (keyCode == VK_UP) {
		_pointY += 1;
	}
	if (keyCode == VK_DOWN) {
		_pointY -= 1;
	}
	if (keyCode == VK_RIGHT) {
		_pointX += 1;
	}
	if (keyCode == VK_LEFT) {
		_pointX -= 1;
	}
	*/
	if (keyCode == VK_HOME) {
		_gControl->getWeaponScale() *= 2;
	}
	if (keyCode == VK_END) {
		_gControl->getWeaponScale() /= 2;
	}
}

void TestWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//

	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
