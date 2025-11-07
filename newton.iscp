export void compute_newton(
    uniform int width,
    uniform int height,
    uniform int n,
    uniform int max_iter,
    uniform float epsilon,
    uniform int* uniform root_indices,
    uniform int* uniform iterations
) 
{
    uniform float size = 4.0f;
    uniform float re_min = -size;
    uniform float re_max = size;
    uniform float im_min = -size;
    uniform float im_max = size;

    // parallel looping 
    foreach (i=0 ... width, j = 0 ... height) {
        
        float x0 = re_min + i * (re_max - re_min) / (width - 1);
        float y0 = im_min + j * (im_max - im_min) / (height - 1);

        float zx = x0;
        float zy = y0;

        int iter = 0;
        int root_index = -1;
        bool lane_done = false;

        for (; iter < max_iter && !lane_done; ++iter) {

            // computing z^(n-1)
            float zx_pow = 1.0f;
            float zy_pow = 0.0f;
            float zx_temp = zx;
            float zy_temp = zy;
            for (int k = 1; k < n; ++k) {
                float tx = zx_pow * zx_temp - zy_pow * zy_temp;
                float ty = zx_pow * zy_temp + zy_pow * zx_temp;
                zx_pow = tx;
                zy_pow = ty;
            }

            float znx = zx * zx_pow - zy * zy_pow;
            float zny = zx * zy_pow + zy * zx_pow;

            // numerator: f(z) = z^n - 1
            float num_x = znx - 1.0f;
            float num_y = zny;

            // denominator: f'(z) = n * z^(n-1)
            float denom_x = n * zx_pow;
            float denom_y = n * zy_pow;

            float denom_mag2 = denom_x*denom_x + denom_y*denom_y;

            // update approximation
            zx = zx - (num_x * denom_x + num_y * denom_y) / denom_mag2;
            zy = zy - (num_y * denom_x - num_x * denom_y) / denom_mag2;
        

            // check for convergence
            for (int k = 0; k < n; ++k) {
                float root_x = cos(2.0f * PI * k / n);
                float root_y = sin(2.0f * PI * k / n);
                float dx = zx - root_x;
                float dy = zy - root_y;
                if (sqrt(dx*dx + dy*dy) < epsilon) {
                    root_index = k;
                    lane_done = true;
                    break;
                }
            }
        }
        root_indices[j*width + i] = root_index;
        iterations[j*width + i] = iter;
    }
}