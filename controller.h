#pragma once
#include "model.h"

namespace s21 {
class Controller {
private:
  Model model_;

public:
  Controller() : model_() {}
  Controller(std::string str, double x, double &result)
      : model_(str, x, result) {}

  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;
  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;
  ~Controller() {}

  int StartCalc();
  double GetRes();

  /******* BONUS *********/
  double CalculateDeposit(double P, double perc, int time, double nalog,
                          double *sum_nalog, int kap, double *final_sum, int n,
                          double sum_pop, double sum_snyat);
  double MonPayAnnuitent(double S, double perc, double n);
  double OverpayAnnuitent(double S, double n, double montly_pay, double *total);
  double OverpayDiff(double S, double perc, double n, double *monthly_payment);
};
} // namespace s21
