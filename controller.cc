#include "controller.h"

namespace s21 {
int Controller::StartCalc() { return model_.start_calc(); }
double Controller::GetRes() { return model_.result; }

//*********  BONUS PART  *********//
double Controller::MonPayAnnuitent(double S, double perc, double n) {
  return model_.monthly_payment_annuitent(S, perc, n);
}

double Controller::OverpayAnnuitent(double S, double n, double montly_pay,
                                    double *total) {
  return model_.overpayment_and_total_annuitent(S, n, montly_pay, total);
}

double Controller::CalculateDeposit(double P, double perc, int time,
                                    double nalog, double *sum_nalog, int kap,
                                    double *final_sum, int n, double sum_pop,
                                    double sum_snyat) {
  return model_.get_deposit_perc(P, perc, time, nalog, sum_nalog, kap,
                                 final_sum, n, sum_pop, sum_snyat);
}

double Controller::OverpayDiff(double S, double perc, double n,
                               double *monthly_payment) {
  return model_.monthly_payment_and_overpay_difference(S, perc, n,
                                                       monthly_payment);
}
} // namespace s21
