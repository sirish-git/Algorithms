/* Fixed point analyis tool */

#include <math.h>

/* Target fixed point bit-depth */
#define TARGET_BIT_W		8
#define TARGET_ACCUM_W		16


float f_weights1[3 * 3] = { 0.967,  0.856,  1.145,
0.456,  0.987,  1.756,
-1.678, -1.987, -2.099 };
float f_weights2[3 * 3] = { 0.967,  0.856,  1.145,
0.456,  0.987,  1.756,
1.678,  1.987,  2.099 };
float f_weights3[3 * 3] = { -0.967, -0.856, -1.145,
-0.456, -0.987, -1.756,
-1.678, -1.987, -2.099 };
float f_weights4[3 * 3] = { 0.067,  0.056,  0.045,
0.056,  0.087,  0.056,
-0.078, -0.087, -0.099 };

//Q indicates ineger part bits
int inp_bw_Q[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int wts_bw_Q[8];
int shf_bw_Q[8];
int out_bw_Q[8];
float *f_wt_buf[8] = { f_weights1, f_weights2, f_weights3, f_weights4 };

int inp_ch, out_ch;
int k_w, k_h;

/* Assumptions/Notes: */
// input weight Q factors are initialized or took from prev layer output
void find_fix_Q()
{
	int ch_i, ch_o;
	int k, flag_neg;
	int w_Q_frac_bits, out_int_bits;;
	float f_val, f_pos_sum, f_neg_sum, f_abs_sum;
	float f_wt_min, f_wt_max;
	float f_bits;
	int i_val, i_bits;
	float *wt_ptr;

	for (ch_o = 0; ch_o < out_ch; ch_o++)
	{
		for (ch_i = 0; ch_i < inp_ch; ch_i++)
		{
			/* Analyze weights */
			{
				wt_ptr = f_wt_buf[ch_i];
				flag_neg = 0;
				f_pos_sum = 0;
				f_neg_sum = 0;
				f_abs_sum = 0;
				f_wt_min = 99999999;
				f_wt_max = -99999999;
				//tbd: may need to find pos, neg sum ranges
				for (k = 0; k < k_w * k_h; k++)
				{
					f_val = wt_ptr[k];
					//find sums
					f_pos_sum += (f_val > 0) ? f_val : 0;
					f_neg_sum += (f_val < 0) ? f_val : 0;
					f_abs_sum += (f_val > 0) ? f_val : -f_val;
					//find min, max
					f_wt_min = (f_val < f_wt_min) ? f_val : f_wt_min;
					f_wt_max = (f_val > f_wt_max) ? f_val : f_wt_max;

					flag_neg = (f_val < 0) ? -1 : flag_neg;
				}
			}

			//find weight Q factors based on min, max wt ranges
			{
				//tbd: to find Q based on accurate -ve, +ve ranges instead of doubling
				f_wt_max = (f_wt_max > -f_wt_min) ? f_wt_max : -f_wt_min;

				//consider negative range, so double the total range
				if (flag_neg == -1)
				{
					f_wt_max *= 2;
				}
				i_val = f_wt_max;

				//find Q: integer & fraction bits
				f_bits = log2f(f_wt_max);
				//store Q factor: int bits
				wts_bw_Q[ch_i] = (f_wt_max > i_val) ? (f_bits + 1) : f_bits;
#if 0
				if (TARGET_BIT_W > wts_bw_Q[ch_i])
				{
					w_Q_frac_bits = TARGET_BIT_W - wts_bw_Q[ch_i];
				}
				else
				{
					//no fraction scaling bits, all bits are required for int in given bit range
					w_Q_frac_bits = 0;
				}
#endif
			}

			//find shift factor
			{
				//consider negative range, so double the total range
				if (flag_neg == -1)
				{
					f_abs_sum *= 2;
				}
				i_val = f_abs_sum;

				//find Q: integer & fraction bits
				f_bits = log2f(f_abs_sum);
				i_bits = (f_abs_sum > i_val) ? (f_bits + 1) : f_bits;
				i_bits += inp_bw_Q[ch_i];

				shf_bw_Q[ch_i] = TARGET_ACCUM_W - i_bits;
			}

			//find output scale factors
			{
				out_bw_Q[ch_i] = inp_bw_Q[ch_i] + i_bits;
			}
		}
	}
}

int main()
{
	k_w = k_h = 3;

	//for first weight
	{
		inp_ch = 1;
		out_ch = 1;
		find_fix_Q();

		//convol float
		//convol fixed
	}

	return 0;
}