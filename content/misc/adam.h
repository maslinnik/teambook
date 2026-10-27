/**
 * Author: Gleb Kostylev
 * Date: 2027-10-27
 * Description: Adam optimizer with heuristics.
 * Status: OK on XIX Open Cup, grand prix of Poland, task A
 */

template <int N, ld epsilon = (ld)1e-8, ld fast_lr_decay = (ld)0.9, ld beta1 = (ld)0.9, ld beta2 = (ld)0.999>
struct Adam {
    // you don't need to type them, just verify that they're true :)
    static_assert(fast_lr_decay > 0 && fast_lr_decay <= 1);
    static_assert(beta1 > 0 && beta1 < 1);
    static_assert(beta2 > 0 && beta2 < 1);

    // in theory, lr should be ~||x_opt - x_0||, but you should be able set it a bit higher
    explicit Adam(ld lr, ld lr_decay = 1, array<ld, N> x = {}): lr(lr), lr_decay(lr_decay), variables(x), best_variables(x) {}
    static Adam auto_decay(int iter, ld lr, array<ld, N> x = {}) {
        return Adam(lr, exp((log(epsilon) - log(lr)) / iter), x);
    }

    // use it in optimization loop like 'for (...; adam && ...; )' to speed up program
    explicit operator bool() const {
        return lr > epsilon;
    }

    void step(ld loss, array<ld, N> grad) {
        if (isnan(loss) || isinf(loss) || loss > min_loss) {
            // rollback
            variables = best_variables;

            // heuristics to prevent further misses (vary them if you want)
            lr *= fast_lr_decay;
            for (int i = 0; i < N; ++i) {
                momentum[i] /= 2;
                impulse[i] /= 2;
            }
            beta1_power = 1;
            beta2_power = 1;
            return;
        }
        min_loss = loss;
        best_variables = variables;
        beta1_power *= beta1;
        beta2_power *= beta2;
        for (int i = 0; i < N; ++i) {
            impulse[i] = impulse[i] * beta1 + (1 - beta1) * grad[i];
            momentum[i] = momentum[i] * beta2 + (1 - beta2) * grad[i] * grad[i];
            ld impulse_corr = impulse[i] / (1 - beta1_power);
            ld momentum_corr = momentum[i] / (1 - beta2_power);
            variables[i] -= lr / (sqrt(momentum_corr) + epsilon) * impulse_corr;
        }
        lr *= lr_decay;
    }

    ld lr;
    ld lr_decay;

    ld beta1_power = 1;
    ld beta2_power = 1;

    ld min_loss = 1e100;
    array<ld, N> best_variables{};

    array<ld, N> variables{};
    array<ld, N> impulse{};
    array<ld, N> momentum{};
};
