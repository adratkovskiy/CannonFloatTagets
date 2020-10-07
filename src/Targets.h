
class Targets
{
public:
	Targets(const float size, const float speed, const FPoint& pos, const FPoint& direction, const int points);
	~Targets();

private:
	float _size;
	float _speed;
	FPoint _pos;
	FPoint _direction;
	int	_points;
};
