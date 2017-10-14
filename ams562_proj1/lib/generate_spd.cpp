#include <random>
#include <ctime>
#include <vector>
#include <cstdint>

namespace playgroud {

using seed_t = std::uint32_t;
using engine_t = std::mt19937;

inline seed_t default_seed() {
    const static seed_t s(static_cast<seed_t>(std::time(0)));
    return s;
}

// class of engine and seed
class EngineSeed {
public:
    EngineSeed() = delete;

private:
    static engine_t e_;
    friend struct random_generator;
};

engine_t EngineSeed::e_(default_seed());


struct random_generator {
    using dist_t = std::uniform_real_distribution<double>;
    inline double gen() const {
        dist_t u(-1.0, 1.0);
        return u(EngineSeed::e_);
    }
};

inline static double rand() {
    random_generator k;
    return k.gen();
}

static inline void construct_random_mat(std::vector<double> &a) {
        for (auto & v:a) v = rand();
}

// implement A*A'
static inline void mtmm(const int n, double ** b, const std::vector<double> &a) {
    using sz_t = std::vector<double>::size_type;
    const sz_t m = n;
    for (sz_t i = 0u; i < m; ++i) {
        const sz_t ld1 = i*m;
        for (sz_t j = 0u; j < m; ++j) {
            const sz_t ld2 = j*m;
            double tmp = 0.0;
            for (sz_t k = 0u; k < m; ++k)
                tmp += a[ld1+k]*a[ld2+k];
            b[i][j] = tmp;
        }
    }
}

}

void generate_spd(const int n, double **A) {
    std::vector<double> tmp(n*n);
    playgroud::construct_random_mat(tmp);
    playgroud::mtmm(n, A, tmp);
}
