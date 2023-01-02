#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list>
#include <map>
#include <string>

struct Node_leksem {
  double value;
  int priority;
  std::pair<std::string, int> type;
};

namespace s21 {
class Model {
public:
  std::string str;
  double x;
  double result;

  Model() : str("_"), x(0.0), result(0.0) {}
  Model(std::string str, const double &x, const double &result)
      : str(str), x(x), result(result) {}
  ~Model() {}

  int start_calc();

  int check_validnost();
  int valid_x(std::string::iterator &tmp_i);
  int valid_nums(std::string::iterator &tmp_i);
  int valid_ariphmetic(std::string::iterator &tmp_i);
  int parse_dot(std::string::iterator &tmp_i, std::string::iterator &i);
  int valid_func(std::string::iterator &tmp_i, std::string::iterator &i);
  int valid_brackets(int &o_b, int &cl_b, std::string::iterator &tmp_i);

  int find_func_valid(std::string::iterator &i, int &code_pov_mod);
  void skip_num(std::string::iterator &i, std::string::iterator &&str_end);
  std::pair<std::string, int> get_type_func(std::string::iterator &i);

  std::list<Node_leksem> *make_leksem();
  std::list<Node_leksem> list_for_notation(std::list<Node_leksem> *list);

  double get_result(std::string operand, double v1, double v2);
  int calculate(std::list<Node_leksem> &for_RPN);

  //  *** BONUS PART ***  //
  double monthly_payment_annuitent(double S, double perc, double n);
  double overpayment_and_total_annuitent(double S, double n, double montly_pay,
                                         double *total);
  double monthly_payment_and_overpay_difference(double S, double perc, double n,
                                                double *monthly_payment);
  double get_deposit_perc(double P, double perc, int time, double nalog,
                          double *sum_nalog, int kap, double *final_sum, int n,
                          double sum_pop, double sum_snyat);
  void replace_symbol(std::string &str, std::string sym_off,
                      std::string sym_on);
};
} // namespace s21
