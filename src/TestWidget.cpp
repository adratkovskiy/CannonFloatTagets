#include "stdafx.h"
#include "TestWidget.h"

void DrawCross(int x, int y) // инструмент, чтобы понять, про какие координаты идет речь
{
	Render::DrawLine(math::Vector3(x - 10, y, 1), math::Vector3(x + 10, y, 1));
	Render::DrawLine(math::Vector3(x, y - 10, 1), math::Vector3(x, y + 10, 1));
}

TestWidget::TestWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _eff(NULL)
{
	Init();
}

void TestWidget::Init()
{
	_options = new Options(); // гружу настройки из xml

	//контроллер для игры
	_gControl = new GameController(GameController::GameStates::START_SCREEN, true, _options->getParamFloat("sys_timer"));
	
	_cannon = new Cannon(_options->getParamFloat("cannon_angle")
		, _options->getParamFloat("gun_scale")
		, _options->getParamFPoint("cannon_stand_pos")
		, _options->getParamFPoint("cannon_rotate_point")
		, _options->getParamFPoint("cannon_center"));
	_cannonball = new Cannonball(_options->getParamFPoint("cannonball_center")
		, _options->getParamFloat("cannonball_speed")
		, _options->getSplinePoints());

	//гружу текстуры
	_cannonBackTexture = Core::resourceManager.Get<Render::Texture>("Cannon_back");
	_cannonFrontTexture = Core::resourceManager.Get<Render::Texture>("Cannon_front");
	_standTexture = Core::resourceManager.Get<Render::Texture>("Stand");
	_backgroundTexture = Core::resourceManager.Get<Render::Texture>("Background");
	_aimTexture = Core::resourceManager.Get<Render::Texture>("Aim");
	_cannonballTexture = Core::resourceManager.Get<Render::Texture>("Cannonball");
}

void TestWidget::Draw()
{
	_gControl->setMousePos(Core::mainInput.GetMousePos());
	
	switch (_gControl->getGameState()) // Будущие режимы игры (заставка, игра, финальный счет)
	{
	case GameController::GameStates::START_SCREEN: // режим: игра
		_backgroundTexture->Draw();		// фон

		Render::device.PushMatrix();		// подставка под пушку
		Render::device.MatrixTranslate(_cannon->getStandPos());
		Render::device.MatrixScale(_cannon->getScale());
		_standTexture->Draw();
		Render::device.PopMatrix();

		//обрати внимание, как рисую
		Render::device.PushMatrix();	//задняя (фоновая часть пушки) 
		Render::device.MatrixTranslate(_cannon->getCannonCenter()); //транслирую матрицу с местоположением рассчетным
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle()); //поворачиваю на угол
		Render::device.MatrixTranslate(_cannon->getCannonRotatePoint()); //еще раз транслирую, чтобы сдвинуть от центра, но при этом после поворота, чтобы центр объекта остался на месте
		Render::device.MatrixScale(_cannon->getScale()); // скейл
		_cannonBackTexture->Draw(); //рисую
		Render::device.PopMatrix();

		if (!_gControl->getReadyToShot())
		{
			FPoint currentPosition = spline.getGlobalFrame(math::clamp(0.0f, 1.0f, _gControl->getTimer() / 6.0f));
			//_cannonball->updPosition(_gControl->getTimer());
			Render::device.PushMatrix();
			Render::device.MatrixTranslate(_cannonball->getPos() + currentPosition);
			//Render::device.MatrixTranslate(currentPosition.x + _cannonball->getPos().x, currentPosition.y + _cannonball->getPos().y, 0);
			//Render::device.MatrixTranslate(currentPosition);
			Render::device.MatrixScale(_cannon->getScale());
			_cannonballTexture->Draw();
			Render::device.PopMatrix();
		}

		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_cannon->getCannonCenter());
		Render::device.MatrixRotate(math::Vector3(0, 0, 1), _cannon->getAngle());
		Render::device.MatrixTranslate(_cannon->getCannonRotatePoint());
		Render::device.MatrixScale(_cannon->getScale());
		_cannonFrontTexture->Draw();
		Render::device.PopMatrix();

		Render::device.PushMatrix();
		Render::device.MatrixTranslate((float)_gControl->getMousePos().x, (float)_gControl->getMousePos().y, 0);
		IRect texRect = _aimTexture->getBitmapRect();
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);
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
	Render::EndColor();
	
	//
	// Опять включаем текстурирование.
	//
	Render::device.SetTexturing(true);
	
	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, "x:" + utils::lexical_cast(_gControl->getMousePos().x) + ", Y:" + utils::lexical_cast(_gControl->getMousePos().y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 65, "gameState:" + utils::lexical_cast(static_cast<int>(_gControl->getGameState())), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 95, "timer:" + utils::lexical_cast(_gControl->getTimer()), 1.f, CenterAlign);
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
	_gControl->changeTimer() += dt * _cannonball->getCannonTimer();
	
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
		//_cannonball->splineClear();
		spline.Clear();
	}	
	
	//
	// Анимирование параметра масштабирования в зависимости от таймера.
	//
		
	_cannon->setAngle( atan2(_cannon->getCannonCenter().y - _gControl->getMousePos().y, _cannon->getCannonCenter().x - _gControl->getMousePos().x) / math::PI * 180 + 90 );
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
		if (_gControl->getReadyToShot())
		{
			_gControl->setReadyToShot(false);
			bool stat = _gControl->getReadyToShot();
			float shotLength = math::sqrt(math::abs(math::sqr(_gControl->getMousePos().x - _cannon->getCannonCenter().x) + math::sqr(_gControl->getMousePos().y - _cannon->getCannonCenter().y)));
			_cannonball->setCannonTimer( 1 / shotLength * _cannonball->getSpeed() );
			
			spline.addKey(0.0f, _cannon->getCannonCenter());
			spline.addKey(0.3f, _gControl->getMousePos());
			spline.addKey(0.5f, { (float)(_gControl->getMousePos().x + (_gControl->getMousePos().x - _cannon->getCannonCenter().x)), (float)(_gControl->getMousePos().y + 0.3 * (_gControl->getMousePos().y - _cannon->getCannonCenter().y)) });
			spline.addKey(0.7f, { (float)(_gControl->getMousePos().x + 2 * (_gControl->getMousePos().x - _cannon->getCannonCenter().x)), (float)(_gControl->getMousePos().y) });
			spline.addKey(1.0f, { (float)(_cannon->getCannonCenter().x + 1.75 * (_gControl->getMousePos().x + (_gControl->getMousePos().x - _cannon->getCannonCenter().x) - _cannon->getCannonCenter().x)), (float)(-30) });
			spline.CalculateGradient();
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
