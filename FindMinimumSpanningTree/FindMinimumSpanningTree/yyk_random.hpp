#ifndef yyk_random_h
#define yyk_random_h
namespace yyk_random {
	static constexpr long yyk_A = 48271;
	static constexpr long yyk_M = 2147483647;
	static constexpr long yyk_Q = yyk_M / yyk_A;
	static constexpr long yyk_R = yyk_M % yyk_A;
	static unsigned long yyk_seed = 1;
	inline void initialize_seed(unsigned long init_val) noexcept
	{
		yyk_seed = init_val;
	}
	long random() noexcept
	{
		long tmpseed = yyk_A * (yyk_seed % yyk_Q) - yyk_R * (yyk_seed / yyk_Q);
		return yyk_seed = tmpseed >= 0 ? tmpseed : tmpseed + yyk_M;
	}
	template<typename T=long>
	class uniform_int_distribution
	{
		public:
			uniform_int_distribution(long a, long b) :
				l(a), r(b) {}
			inline  T  operator()() noexcept
			{
			   return    static_cast<T>(l + random() % (r - l + 1));
			}

	private:
		long l, r;
	};
	template<typename T = double>
	class uniform_real_distribution
	{
	public:
		uniform_real_distribution(T a, T b) :
			l(a), r(b) {}
		inline T operator()() noexcept {
			return (r - l) * static_cast<T>(random()) / yyk_M + l;
		}
	private:
		T l, r;
	};
}
#endif
