#include <string>

enum {
	ent_Student,
	ent_PizzaPlaceOwner,
	ent_Delivery
};

inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Student:
		return std::string{"Student Kim"};
	case ent_PizzaPlaceOwner:
		return std::string{ "PizzaPlaceOwner Lee" };
	case ent_Delivery:
		return std::string{ "Delivery Park" };
	}
}