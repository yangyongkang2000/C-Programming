#ifndef yyk_random_h
#define yyk_random_h
namespace yyk_random {
	static constexpr long A = 48271;
	static constexpr long M = 2147483647;
	static constexpr long Q = M / A;
	static constexpr long R = M % A;
	static unsigned long seed = 1;
	inline void initialize_seed(unsigned long init_val) noexcept
	{
		seed = init_val;
	}
	long random() noexcept
	{
		long tmpseed = A * (seed % Q) - R * (seed / Q);
		return seed = tmpseed >= 0 ? tmpseed : tmpseed + M;
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
			return (r - l) * static_cast<T>(random()) / M + l;
		}
	private:
		T l, r;
	};
}
#endif
