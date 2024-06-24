
#include "Precompiled.h"
#include "SoftRenderer.h"
#include <random>
#include <math.h>

using namespace CK::DD;

// ���ڸ� �׸��� �Լ�
void SoftRenderer::DrawGizmo2D()
{
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	LinearColor gridColor(LinearColor(0.8f, 0.8f, 0.8f, 0.3f));

	Vector2 viewPos = g.GetMainCamera().GetTransform().GetPosition();
	Vector2 extent = Vector2(_ScreenSize.X * 0.5f, _ScreenSize.Y * 0.5f);

	int xGridCount = _ScreenSize.X / _Grid2DUnit;
	int yGridCount = _ScreenSize.Y / _Grid2DUnit;

	Vector2 minPos = viewPos - extent;
	Vector2 minGridPos = Vector2(ceilf(minPos.X / (float)_Grid2DUnit), ceilf(minPos.Y / (float)_Grid2DUnit)) * (float)_Grid2DUnit;
	ScreenPoint gridBottomLeft = ScreenPoint::ToScreenCoordinate(_ScreenSize, minGridPos - viewPos);

	for (int ix = 0; ix < xGridCount; ++ix)
	{
		r.DrawFullVerticalLine(gridBottomLeft.X + ix * _Grid2DUnit, gridColor);
	}

	for (int iy = 0; iy < yGridCount; ++iy)
	{
		r.DrawFullHorizontalLine(gridBottomLeft.Y - iy * _Grid2DUnit, gridColor);
	}

	ScreenPoint worldOrigin = ScreenPoint::ToScreenCoordinate(_ScreenSize, -viewPos);
	r.DrawFullHorizontalLine(worldOrigin.Y, LinearColor::Red);
	r.DrawFullVerticalLine(worldOrigin.X, LinearColor::Green);
}

// ���� ������Ʈ ���


// ���� �� �ε��� ����ϴ� �Լ�
void SoftRenderer::LoadScene2D()
{
	// ���� �� �ε����� ����ϴ� ��� �� �ֿ� ���۷���
	auto& g = Get2DGameEngine();

}

// 게임 로직과 렌더링 로직 공유하는 변수 영역
Vector2 currentPosition(0.f, 0.f);


// 게임 로직 담당 함수
void SoftRenderer::Update2D(float InDeltaSeconds)
{
	// 게임 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& g = Get2DGameEngine();
	const InputManager& input = g.GetInputManager();

	// 게임 로직 로컬 변수
	static float moveSpeed = 10.f;

	// 함수로 처리했지만 사실 enum 기반으로 n번째 배열 값을 가져오는 작업
	Vector2 inputVector = Vector2(input.GetAxis(InputAxis::XAxis), input.GetAxis(InputAxis::YAxis)).GetNormalize();
	Vector2 deltaPos = inputVector * moveSpeed * InDeltaSeconds;

	currentPosition += deltaPos;
}

void SoftRenderer::DrawCrossPoint(RendererInterface& Render, const Vector2 pos, const LinearColor color) {
	Render.DrawPoint(currentPosition, color);
	Render.DrawPoint(currentPosition + Vector2::UnitX, color);
	Render.DrawPoint(currentPosition - Vector2::UnitX, color);
	Render.DrawPoint(currentPosition + Vector2::UnitY, color);
	Render.DrawPoint(currentPosition - Vector2::UnitY, color);
}

// 렌더링 로직 담당 함수
void SoftRenderer::Render2D()
{
	// 렌더링 로직에서 사용하는 모듈 내 주요 레퍼런스
	auto& r = GetRenderer();
	const auto& g = Get2DGameEngine();

	// 배경 격자 그리기
	DrawGizmo2D();

	// 렌더링 로컬 변수

	// 선 그리기
	// static float lineLen = 500.f;
	// Vector2 lineStart = currentPosition * lineLen;
	// Vector2 lineEnd = currentPosition * -lineLen;
	// r.DrawLine(lineStart, lineEnd, LinearColor::LightGray);

	// DrawCrossPoint(r, currentPosition, LinearColor::Blue);

	// 원 그리기
	static float radius = 100.f;
	static std::vector<Vector2> circles;

	if (circles.empty()) {
		for (float x = -radius; x <= radius; ++x) {
			for (float y = -radius; y <= radius; ++y) {
				Vector2 pointToTest = Vector2(x, y);
				float squareLen = pointToTest.SizeSquared();
				if (squareLen <= pow(radius, 2))
					circles.push_back(pointToTest);
			}
		}
	}

	for (const auto& v : circles) {
		r.DrawPoint(v + currentPosition, LinearColor::Red);
	}

	r.PushStatisticText("Coord: " + currentPosition.ToString());
}

// �޽ø� �׸��� �Լ�
void SoftRenderer::DrawMesh2D(const class DD::Mesh& InMesh, const Matrix3x3& InMatrix, const LinearColor& InColor)
{
}

// �ﰢ���� �׸��� �Լ�
void SoftRenderer::DrawTriangle2D(std::vector<DD::Vertex2D>& InVertices, const LinearColor& InColor, FillMode InFillMode)
{
}
