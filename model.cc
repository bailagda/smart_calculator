#include "model.h"
#include <cstring>
#include <list>
#include <string>
#include <tuple>

#include <iostream>
#include <list>

std::map<std::string, int> func_type{
    {"cos", 0},      {"sin", 1},       {"tan", 2},   {"acos", 3},
    {"asin", 4},     {"atan", 5},      {"sqrt", 6},  {"ln", 7},
    {"log", 8},      {"mod", 9},

    {"number", 10},

    {"open_br", 11}, {"close_br", 12},

    {"add", 13},     {"sub", 14},      {"mult", 15}, {"division", 16},
    {"pow", 17}};

std::string cstalmp = "cstalmpx";

// ***************************************************************************

int s21::Model::find_func_valid(std::string::iterator &i, int &code_pov_mod) {
  int exit_code = 0;

  if (strstr(i.base(), "acos")) {
    std::advance(i, 3);
  } else if ((strstr(i.base(), "asin"))) {
    std::advance(i, 3);
  } else if ((strstr(i.base(), "atan"))) {
    std::advance(i, 3);
  } else if ((strstr(i.base(), "cos"))) {
    std::advance(i, 2);
  } else if ((strstr(i.base(), "sin"))) {
    std::advance(i, 2);
  } else if ((strstr(i.base(), "tan"))) {
    std::advance(i, 2);
  } else if ((strstr(i.base(), "sqrt"))) {
    std::advance(i, 3);
  } else if ((strstr(i.base(), "log"))) {
    std::advance(i, 2);
  } else if ((strstr(i.base(), "ln"))) {
    *i++;
  } else if ((strstr(i.base(), "mod"))) {
    std::advance(i, 2);
    code_pov_mod = 1;
  } else if ((strstr(i.base(), "pow"))) {
    std::advance(i, 2);
    code_pov_mod = 1;
  } else if ((strstr(i.base(), "x"))) {
    *i++;
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int s21::Model::parse_dot(std::string::iterator &tmp_i,
                          std::string::iterator &i) {
  int error = 0;
  if (*(tmp_i - 1) < '0' || *(tmp_i - 1) > '9') {
    error = 1;
  } else {
    while ((*i >= '0' && *i <= '9') || *i == '.') {
      if (*i == '.')
        error += 1;
      ++i;
    }
    --i;
    error -= 1;
  }
  return (error);
}

int s21::Model::valid_x(std::string::iterator &tmp_i) {
  int err = 0;
  if (*(tmp_i + 1) == 'x') {
    err = 1;
  }
  return err;
}

int s21::Model::valid_nums(std::string::iterator &tmp_i) {
  int err = 0;
  if (*(tmp_i + 1) == '.') {
    if (*(tmp_i + 2) < '0' || *(tmp_i + 2) > '9') {
      err = 1;
    }
  }
  return err;
}

int s21::Model::valid_ariphmetic(std::string::iterator &tmp_i) {
  int err = 0;
  if ((*(tmp_i + 1) < '0' || *(tmp_i + 1) > '9')) {
    if (*(tmp_i + 1) == '(' || *(tmp_i - 1) == ')') {
    } else if (cstalmp.find(*(tmp_i + 1)) == std::string::npos)
      err = 1;
  } else if ((*tmp_i != 0 && (*(tmp_i - 1) < '0' || *(tmp_i - 1) > '9')) &&
             *(tmp_i - 1) != 41) {
    if (*(tmp_i - 1) == '(' || *(tmp_i - 1) == 'x') {
    } else
      err = 1;
  }
  return err;
}

int s21::Model::valid_func(std::string::iterator &tmp_i,
                           std::string::iterator &i) {
  int code_pov_mod = 0;
  auto func_begin = i;
  int err = find_func_valid(tmp_i, code_pov_mod);
  i = tmp_i;
  if (code_pov_mod == 0 && *(tmp_i + 1) != '(') {
    err = 1;
  } else if (code_pov_mod == 1) {
    if (!isdigit(*(func_begin-1)) && (*(func_begin-1) != ')')) {
      err = 1;
    }
  }
  return err;
}

int s21::Model::valid_brackets(int &o_b, int &cl_b,
                               std::string::iterator &tmp_i) {
  int err = 0;
  if (*tmp_i == '(') {
    if ((*(tmp_i - 1) >= '0' && *(tmp_i - 1) <= '9') || *(tmp_i - 1) == ')') {
      err = 1;
    } else
      o_b += 1;
  } else if (*tmp_i == ')') {
    if ((*(tmp_i + 1) >= '0' && *(tmp_i + 1) <= '9') || *(tmp_i + 1) == '(') {
      err = 1;
    } else
      cl_b += 1;
  }
  return err;
}

int s21::Model::check_validnost() {
  int err = 0;
  int open_br = 0;
  int close_br = 0;

  for (auto i = str.begin(); (i != str.end()) && (err != 1); i++) {
    auto tmp_i = i;
    if (*tmp_i == 'x') {
      err = valid_x(tmp_i);
    } else if ((*tmp_i >= '0' && *tmp_i <= '9') || *tmp_i == 'x') {
      err = valid_nums(tmp_i);
    } else if (*tmp_i == '.') {
      err = parse_dot(tmp_i, i);
    } else if (*tmp_i == '*' || *tmp_i == '+' || *tmp_i == '-' ||
               *tmp_i == '/' || *tmp_i == '^') {
      err = valid_ariphmetic(tmp_i);
    } else if (*tmp_i == '(' || *tmp_i == ')') {
      err = valid_brackets(open_br, close_br, tmp_i);
    } else if (cstalmp.find(*tmp_i) != std::string::npos) {
      err = valid_func(tmp_i, i);
    } else {
      err = 1;
    }
  }
  if (close_br != open_br)
    err = 1;
  return err;
}

std::pair<std::string, int>
s21::Model::get_type_func(std::string::iterator &i) {
  std::string type;
  for (auto j = type.begin(); (*i >= 'a') && (*i <= 'z'); j++, i++) {
    type.insert(j, *i);
  }
  auto m_tmp = *func_type.find(type);
  std::pair<std::string, int> p = {(m_tmp).first, (m_tmp).second};
  i--;
  return (p);
}

std::list<Node_leksem> *s21::Model::make_leksem() {
  std::list<Node_leksem> *result = new std::list<Node_leksem>;
  Node_leksem for_RPN;
  for (auto i = str.begin(); *i != '\0';) {
    for_RPN.value = 0.0;
    for_RPN.priority = 0;
    if (isdigit(*i)) {
      std::string tmp(str.length() + 1, '\0');
      for (int j = 0; (*i >= '0' && *i <= '9') || (*i == '.'); ++j, ++i) {
        if (*i != *str.end())
          tmp[j] = *i;
      }
      for_RPN.value = stof(tmp);
      for_RPN.type = *(func_type.find("number"));
    } else if (*i >= 'a' && *i <= 'x') { // functions
      for_RPN.priority = 4;
      if (*i == 'x') {
        for_RPN.priority = 0;
        for_RPN.value = x;
        for_RPN.type = *(func_type.find("number"));
      } else {
        for_RPN.type = get_type_func(i);
        if (for_RPN.type.first == "mod" ||
            for_RPN.type.first == "pow") { // for func 'mod' 'pow'
          for_RPN.priority = 2;
        }
      }
      i++;
    } else if (*i == '(' || *i == ')') {
      for_RPN.type = (*i == '(') ? *(func_type.find("open_br"))
                                 : *(func_type.find("close_br"));
      i++;
    } else if (*i == '+' || *i == '-') {
      auto i_tmp = i;
      if (*i == 0 || *(i_tmp - 1) == '(') { // unary
        for_RPN.type = *(func_type.find("number"));
        result->push_back(for_RPN);
      }
      for_RPN.priority = 1;
      for_RPN.type =
          (*i == '+') ? *(func_type.find("add")) : *(func_type.find("sub"));
      i++;
    } else if (*i == '*' || *i == '/') {
      for_RPN.priority = 2;
      for_RPN.type = (*i == '*') ? *(func_type.find("mult"))
                                 : *(func_type.find("division"));
      i++;
    } else if (*i == '^') {
      for_RPN.priority = 3;
      for_RPN.type = *(func_type.find("pow"));
      i++;
    }
    result->push_back(for_RPN);
  }
  return result;
}

void upload_stack(std::list<Node_leksem> &stack,
                  std::list<Node_leksem> &output_queue) {
  stack.reverse();
  for (auto i = stack.begin(); i != stack.end(); ++i) {
    output_queue.push_back(*i);
    stack.pop_front();
  }
}

std::list<Node_leksem>
s21::Model::list_for_notation(std::list<Node_leksem> *list_before) {
  std::list<Node_leksem> output_queue;
  std::list<Node_leksem> stack;

  auto stack_it = stack.begin();
  auto list = list_before->begin();
  while (list != list_before->end()) {
    if (list->type.first == "number") {
      output_queue.push_back(*list);
    } else if (list->type.first == "open_br" ||
               (list->type.second >= 0 && list->type.second <= 8)) {
      stack.push_back(*list);
    } else if (list->type.first == "mod" ||
               (list->type.second >= 13 && list->type.second <= 17)) {
      if (!stack.empty()) {
        while (stack.back().priority >= (*list).priority && !stack.empty()) {
          output_queue.push_back(stack.back());
          stack.pop_back();
        }
      }
      stack.push_back(*list);
    } else if (list->type.first == "close_br") {
      while (stack.back().type.first != "open_br") {
        output_queue.push_back(stack.back());
        stack.pop_back();
      }
      stack.pop_back();
    } else {
      while (stack_it != stack.end()) {
        output_queue.push_back(*stack_it);
        stack_it++;
      }
    }
    list++;
  }
  upload_stack(stack, output_queue);
  delete list_before;
  return output_queue;
}

void s21::Model::replace_symbol(std::string &str, std::string sym_off,
                                std::string sym_on) {
  size_t pos;
  while ((pos = str.find(sym_off)) != str.npos) {
    str.replace(pos, sym_off.size(), sym_on);
  }
}

double s21::Model::get_result(std::string operand, double v1, double v2) {
  double res = 0.0;
  // double k = M_PI / 180;
  if (operand == "add")
    res = (v1 + v2);
  else if (operand == "sub")
    res = (v1 - v2);
  else if (operand == "division")
    res = (v1 / v2);
  else if (operand == "mult")
    res = (v1 * v2);
  else if (operand == "mod")
    res = fmod(v1, v2);
  else if (operand == "pow")
    res = pow(v1, v2);
  else if (operand == "cos")
    res = cos(v1);
  else if (operand == "sin")
    res = sin(v1);
  else if (operand == "tan")
    res = tan(v1);
  else if (operand == "acos")
    res = acos(v1);
  else if (operand == "asin")
    res = asin(v1);
  else if (operand == "atan")
    res = atan(v1);
  else if (operand == "sqrt")
    res = sqrt(v1);
  else if (operand == "ln")
    res = log(v1);
  else if (operand == "log")
    res = log10(v1);

  return res;
}

int s21::Model::calculate(std::list<Node_leksem> &for_RPN_before) {
  std::list<Node_leksem> stack;
  int err = 0;
  double res = 0;
  double v1 = 0.0;
  double v2 = 0.0;
  auto for_RPN = for_RPN_before.begin();

  while (for_RPN != for_RPN_before.end()) {
    if (for_RPN->type.first == "number") {
      stack.push_back(*for_RPN);
    } else if ((for_RPN->type.second >= 13 && for_RPN->type.second <= 17) ||
               for_RPN->type.second == 9) {
      v2 = stack.back().value;
      stack.pop_back();
      v1 = stack.back().value;
      stack.pop_back();
      res = get_result((*for_RPN).type.first, v1, v2);
      stack.push_back({res, 0, {"number", 10}});
    } else if (for_RPN->type.second >= 0 && for_RPN->type.second <= 8) {
      v1 = (stack.back()).value;
      stack.pop_back();
      res = get_result((*for_RPN).type.first, v1, v2);
      stack.push_back({res, 0, {"number", 10}});
    }
    ++for_RPN;
  }

  result = (*stack.begin()).value;
  stack.clear();

  return err;
}

int s21::Model::start_calc() {
  int err = 0;

  replace_symbol(str, "e-", "/10pow");
  replace_symbol(str, "e+", "*10pow");
  replace_symbol(str, " ", "");

  err = check_validnost();
  if (err == 0) {
    std::list<Node_leksem> for_RPN = list_for_notation(make_leksem());
    err = calculate(for_RPN);
  }
  return err;
}
