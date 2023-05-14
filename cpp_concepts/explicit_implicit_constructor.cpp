class MyClass {
public:
  // explicit MyClass(int i) : i(i) {}
  MyClass(int i) : i(i) {}

private:
  int i;
};

int main() {
  MyClass clz = MyClass(2);
  MyClass clz_2 = 2;
}