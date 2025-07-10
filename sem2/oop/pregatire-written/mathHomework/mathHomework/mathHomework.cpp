#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Expression {
public:
	virtual double evaluate() = 0;
	virtual ~Expression() {};
};

class Constant : public Expression {
private:
	double value;
public:
	Constant(double val) : value(val) {}
	double evaluate() override {
		return value;
	}
};

class UnaryExpression : public Expression {
protected:
	Expression* right; //why do i need a pointer here?
public:
	UnaryExpression(Expression* expr) : right(expr) {}
	double evaluate() override {
		return right->evaluate();
	}
	~UnaryExpression() {
		delete right;
	}
};

class Negation : public UnaryExpression {
public:
	Negation(Expression* expr) : UnaryExpression(expr) {}
	double evaluate() override {
		return -UnaryExpression::evaluate(); //why does this work? how does it negate it?
	}
};

class BinaryExpression : public UnaryExpression {
protected:
	Expression* left;
public:
	BinaryExpression(Expression* expr2, Expression* expr) : UnaryExpression(expr), left(expr2) {}
	double evaluate() override {
		return UnaryExpression::evaluate();
	}
	~BinaryExpression() {
		delete left;
	}
};

class Adder : public BinaryExpression {
public:
	Adder(Expression* expr, Expression* expr2) : BinaryExpression(expr, expr2) {}
	double evaluate() override {
		return left->evaluate() + right->evaluate();
	}
};

class Subtractor : public BinaryExpression {
public:
	Subtractor(Expression* expr, Expression* expr2) : BinaryExpression(expr, expr2) {}
	double evaluate() override {
		return left->evaluate() - right->evaluate();
	}
};

class MathHomework {
private:
	vector<unique_ptr<Expression>> exprs;
public:
	void addExpression(Expression* e) {
		exprs.push_back(unique_ptr<Expression>(e));
	}
	vector<double> getResults() {
		vector<double> results;
		for (auto& ex : exprs) {
			results.push_back(ex->evaluate());
		}
		return results;
	}
};

int main()
{
	Expression* c1 = new Constant{ 5 },
		* c2 = new Constant{ 9 },
		* c3 = new Constant{ 3 };

	Expression* neg = new Negation{ c1 };
	auto* paranthesis = new Subtractor{ c2, c3 };
	auto* res = new Adder{ neg, paranthesis };

	MathHomework hw{};
	hw.addExpression(res);

	auto results = hw.getResults();
	cout << results[0];
}
