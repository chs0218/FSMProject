#include <string>

enum {
	ent_Student,
	ent_PizzaStoreOwner,
	ent_Delivery
};

inline std::string GetNameOfEntity(int n)
{
	switch (n)
	{
	case ent_Student:
		return std::string{"Student Kim"};
	case ent_PizzaStoreOwner:
		return std::string{ "PizzaStoreOwner Lee" };
	case ent_Delivery:
		return std::string{ "Delivery Park" };
	}
}