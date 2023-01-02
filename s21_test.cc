#include "model.h"
// #include <check.h>
#include "gtest/gtest.h"

int err = 0;
s21::Model m;

TEST(calc_tests, case_1) {
  m.str = "1+((2-3";
  err = m.start_calc();
  EXPECT_EQ(err, 1);
}

TEST(calc_tests, case_2) {
  m.str = "1+2-3";
  err = m.start_calc();
  EXPECT_EQ(m.result, 1+2-3);
}
TEST(calc_tests, case_3) {
  m.str = "1-2*12-3pow2";
  err = m.start_calc();
  EXPECT_EQ(m.result, -32);
}
TEST(calc_tests, case_4) {
  m.str = "sin(12)-3";
  err = m.start_calc();
  EXPECT_EQ(m.result, sin(12) - 3);
}
TEST(calc_tests, case_5) {
 m.str = "12pow3";
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, pow(12, 3.0));
}

TEST(calc_tests, case_6) { 
 m.str = "1+2-3*sin(30)";
 double k = 30;
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, 1+2-3*sin(k));
}
TEST(calc_tests, case_7) {
 m.str = "cos(-5)+((10/(5/7))pow2)";
  err = m.start_calc();
  std::cout << m.result << '\n';
  m.result*= 1000000;
  EXPECT_DOUBLE_EQ((int)m.result, 196283662);
}

TEST(calc_tests, case_8) {
 m.str = "1+2-3*log(10)";
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, 1 + 2 - 3*1);
}
TEST(calc_tests, case_9) {
  double k = 12;
 m.str = "cos(cos(12))-3-5";
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, cos(cos(k)) - 3 - 5);

}
TEST(calc_tests, case_10) {
 m.str = "sin(3pow3)-12+(-11+20)";
    err = m.start_calc();
    EXPECT_DOUBLE_EQ(m.result, sin((27)) - 12 + (-11 + 20));
 
}
TEST(calc_tests, case_11) {
 m.str = "sqrt(atan(12))";
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, sqrt(atan(12)));

}
TEST(calc_tests, case_12) {
 m.str = "asin(1)+5pow2";
  err = m.start_calc();
  EXPECT_DOUBLE_EQ(m.result, asin(1)+ pow(5, 2));
}
TEST(calc_tests, case_13) {
 m.str = "1.2.";
  err = m.start_calc();
  EXPECT_EQ(err, 1);
}
TEST(calc_tests, case_14) {
 m.str = "xx";
    err = m.start_calc();
    EXPECT_EQ(err, 1);
}
TEST(calc_tests, case_15) {
 m.str = "ksusha";
  err = m.start_calc();
  EXPECT_EQ(err, 1);
}

START_TEST(bonus_tests) {
    double S = 100000;
    double n = 2.0;
    double perc = 5;
    double total = 0.0;
    double montly_pay = 0.0;

    montly_pay = monthly_payment_annuitent(S, perc, n);
    EXPECT_EQ((int)montly_pay, 4387);
    double ower_pay = overpayment_and_total_annuitent(S, n, montly_pay, &total);
    ck_assert_int_eq((int)ower_pay, 5291);

    double m_pay[24];
    ower_pay = monthly_payment_and_overpay_difference(S, perc, n, m_pay);
    ck_assert_int_eq((int)ower_pay, 105208);
    ck_assert_int_eq((int)m_pay[0], 4583);

    S = 9800;
    int time = 6;
    double nalog = 13;
    double sum_nalog = 0.0;
    double final_sum = 0.0;
    n = 12;
    double profit = get_deposit_perc(S, perc, time, nalog, &sum_nalog, 1, &final_sum, n, 0, 0);
    ck_assert_int_eq((int)profit, 247);

    S = 98000000000;
    profit = get_deposit_perc(S, perc, time, nalog, &sum_nalog, 0, &final_sum, n, 0, 0);
    ck_assert_int_eq((int)profit, 2131500000);
}
END_TEST

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

