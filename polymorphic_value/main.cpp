#include <iostream>
#include <utility>

#include <polymorphic_value.h>

class Vehicle
{
private:
  class Interface
  {
  public:
    virtual ~Interface() = default;
    virtual void drive() = 0;
  };

  template <typename ImplementationType>
  class Delegator : public Interface
  {
  public:
    explicit Delegator(const ImplementationType& implementation)
      : m_implementation{implementation}
    {
    }

    explicit Delegator(ImplementationType&& implementation)
      : m_implementation{std::move(implementation)}
    {
    }

    void drive() override
    {
      m_implementation.drive();
    }

  private:
    ImplementationType m_implementation;
  };

public:
  template <typename ImplementationType>
  explicit Vehicle(ImplementationType&& implementation)
    : m_value{
        std::in_place_type<Delegator<ImplementationType>>,
        Delegator<ImplementationType>{std::forward<ImplementationType>(implementation)}
  }
  {
  }

  void drive()
  {
    m_value->drive();
  }

private:
  isocpp_p0201::polymorphic_value<Interface> m_value;
};

class Car
{
public:
  void drive()
  {
    std::cout << "Vroom, vroom. I'm a car!\n";
  }
};

class Truck
{
public:
  void drive()
  {
    std::cout << "VROOOM. I'm a truck!\n";
  }
};

int main()
{
  Vehicle vehicle{Car{}};
  vehicle.drive();

  vehicle = Vehicle{Truck{}};
  vehicle.drive();
}
