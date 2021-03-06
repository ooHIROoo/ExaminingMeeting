#include "Math.h"
#include <cmath>

namespace Math{

	//　角度を取得
	float GetAngle(const Vec2f &vec_a, const Vec2f &vec_b, const Vec2f &origin, bool is_degree){

		Vec2f diff_a = GetDiff(vec_a, origin);
		Vec2f diff_b = GetDiff(vec_b, origin);

		float length_a = GetDistance(diff_a);
		float length_b = GetDistance(diff_b);

		float cos_theta = GetScalarProduct(diff_a, diff_b) / (length_a*length_b);

		float theta = std::acosf(cos_theta);
		if (is_degree){
			theta = theta * 180 / static_cast<float>(M_PI);
		}
		return theta;
	}

	//　距離を取得
	inline double GetDistance(const Vec2f &vec){
		return (std::sqrt(vec.x()*vec.x() + vec.y()*vec.y()));
	}

	//　内積を取得
	inline double GetScalarProduct(const Vec2f &vec_a, const Vec2f &vec_b){
		return (vec_a.x()*vec_b.x() + vec_a.y()*vec_b.y());
	}

	//　2点間の距離を取得
	double Get2Distance(const Vec2f &vec_a, const Vec2f &vec_b){
		Vec2f length = vec_a - vec_b;
		return (std::sqrt(length.x()*length.x() + length.y()*length.y()));
	}

	//　2点間の距離を取得
	float Get2Distancef(const Vec2f &vec_a, const Vec2f &vec_b){
		Vec2f length = vec_a - vec_b;
		return (std::sqrt(length.x()*length.x() + length.y()*length.y()));
	}

	//　2点間の差(vec_a - vec_b)
	inline Vec2f GetDiff(const Vec2f &vec_a, const Vec2f &vec_b){
		return vec_a - vec_b;
	}
}