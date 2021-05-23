//
//  simpson.hpp
//  naive_integral
//
//  Created by 杨永康 on 2021/4/25.
//

#ifndef simpson_h
#define simpson_h
namespace demo {
/*作者：向阳
链接：https://www.zhihu.com/question/456136707/answer/1851455902
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
// 辛普森公式, 计算[a, b]上积分的近似值
template<typename real,typename F>
inline constexpr real simpsonApprox(F f,real a, real b) noexcept
{
    return ((b - a) / 6.0) * (f(a) + 4.0 * f((a + b) / 2.0f) + f(b));
}
// 计算a, b上的积分, 使用自适应辛普森法
template<typename real,typename F>
inline constexpr real simpson(F f,std::pair<std::pair<real, real>, real> const & p) noexcept
{
    real a=p.first.first;
    real b=p.first.second;
    real epsilon=p.second;
    real c = (a + b) / 2.0;
    real l = simpsonApprox(f,a, c);
    real r = simpsonApprox(f,c, b);
    real t = simpsonApprox(f,a, b);
    if (fabs(l + r - t) < 15.0 * epsilon)
    {
        return l + r + (l + r - t) / 15.0;
    }
    else {
        return simpson<real>(f,{std::pair<real, real>{a, c}, epsilon / 2.0}) + simpson<real>(f,{std::pair<real, real>{c, b}, epsilon / 2.0});
    }
}
}

#endif /* simpson_h */
