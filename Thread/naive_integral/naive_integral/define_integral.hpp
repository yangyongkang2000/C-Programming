//
//  define_integral.hpp
//  naive_integral
//
//  Created by 杨永康 on 2021/4/25.
//

#ifndef define_integral_h
#define define_integral_h
namespace demo {
template<typename T,typename F>
T definite_integral(F f,std::pair<std::pair<T, T>,T> const &q) noexcept
{
    T a=q.first.first;
    T b=q.first.second;
    T eps=q.second;
    int n, k;
    double fa, fb, h, t1, p, s, x, t;
    fa = f(a);
    fb = f(b);
    n = 1;
    h = b - a;
    t1 = h * (fa + fb) / 2.0;
    p = eps + 1.0;
    while (p>=eps)
    {
        s = 0.0;
        for (k = 0; k <= n - 1; ++k)
        {
            x = a + (k + 0.5) * h;
            s = s + (*f)(x);
        }
        t = (t1 + h * s) / 2.0;
        p = fabs(t1 - t);
        t1 = t;
        n = 2 * n;
        h = h / 2.0;
    }
    return t;
}

/*作者：禽兽狼
链接：https://www.zhihu.com/question/456136707/answer/1850887323
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/

}
#endif /* define_integral_h */
