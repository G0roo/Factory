#include <iostream>
#include <vector>//ensuring vectors can be used
#include <string>//dynamic memeory allocation
#include <set>//stores unique elements in each set


using namespace std;



//enums for the DiscountType in Artifact and Service classes used for calculating effective rate 
enum DiscountType { AmountDiscount, PercentageDiscount };
enum RateDiscountType { AmountRateDiscount, PercentageRateDiscount };

set<string>DivisionGUIDs;
set<string>ArtifactGUIDs;
set<string>ServiceGUIDs;

class Division {
protected:
	string GUID;
	string Name;
	string PhoneNumber;
	string Description;
	Division* Parent;

public:
	//Division constructor
	Division(string guid, string name, string phoneNumber, string description, Division* parent = nullptr)
		: GUID(guid), Name(name), PhoneNumber(phoneNumber), Description(description), Parent(parent)
	{
		if (DivisionGUIDs.find(GUID) != DivisionGUIDs.end()) {
			throw invalid_argument("Division GUID must be unique.");
		}
		DivisionGUIDs.insert(GUID);
	}




};

class Artifact {
protected:
	string GUID;
	string Name;
	string Description;
	string Category;
	Division* division;
	double Price;
	double Discount;
	DiscountType discountType;
	int Quantity;

public:
	//Artifact constructor
	Artifact(string guid, string name, string description, string category, Division* division, double price, double discount, DiscountType discountType, int quantity)
		: GUID(guid), Name(name), Description(description), Category(category), division(division), Price(price), Discount(discount), discountType(discountType), Quantity(quantity)
	{
		//ensuring division is not null and that price, discount, and quantity are positive
		if (division == nullptr) {
			throw invalid_argument("Artifact cannot be empty.");
		}
		if (Price < 0) {
			throw invalid_argument("Price cannot be negative.");
		}
		if (Discount < 0) {
			throw invalid_argument("Discount cannot be negative.");
		}
		if (Quantity < 0) {
			throw invalid_argument("Quantity cannot be negative.");
		}

		if (ArtifactGUIDs.find(GUID) != ArtifactGUIDs.end()) {
			throw invalid_argument("Artifact GUID must be unique.");
		}
	}
	//Get the effective price of the Artifact class
	double GetEffectivePrice()
	{

		if (discountType == AmountDiscount) {
			if (Price - Discount < 0) {
				throw invalid_argument("Effective price cannot be negative.");
			}
			else {
				return Price - Discount;
			}
		}
		else {//discountType==PercentageDiscount
			if (Price - Price * Discount / 100.0 < 0) {// ensuring it is not negative
				throw invalid_argument("Effective price cannot be negative.");
			}
			else {
				return Price - (Price * Discount / 100.0);
			}
		}
	}
	//Get total price of Artifact class
	double GetTotalPrice() {
		if (Quantity * GetEffectivePrice() < 0) { //ensuring it is not zero
			throw("Total price cannot be negative.");
		}
		else {
			return Quantity * GetEffectivePrice();
		}
	}

	string GetName() {
		return Name;
	}
};
//Service inherits Artifact
class Service : public Artifact {
protected:
	double Duration;
	double Rate;
	double RateDiscount;
	RateDiscountType rateDiscountType;

public:
	//Service constructor
	Service(string guid, string name, string description, string category, Division* division, double price, double discount, DiscountType discountType, int quantity, double duration, double rate,
		double rateDiscount, RateDiscountType rateDiscountType)
		: Artifact(guid, name, description, category, division, price, discount, discountType, quantity), Duration(duration), Rate(rate), RateDiscount(rateDiscount), rateDiscountType(rateDiscountType)
	{
		//ensuring duration, rate, and rate discount are not<0
		if (Duration < 0) {
			throw invalid_argument("Duration cannot be negative.");
		}
		if (Rate < 0) {
			throw invalid_argument("Rate cannot be negative.");
		}
		if (RateDiscount < 0)
		{
			throw invalid_argument("Rate Discount cannot be negative.");
		}
		if (ServiceGUIDs.find(GUID) != ServiceGUIDs.end()) {
			throw invalid_argument("Error: Service GUID must be unique.");
		}
	}
	//Get the effective rate of the Service class
	double GetEffectiveRate() {
		if (rateDiscountType == AmountRateDiscount) {
			if (Rate - RateDiscount < 0) {//ensuring it is not negative
				throw invalid_argument("Effective rate cannot be negative.");
			}
			return Rate - RateDiscount;
		}
		else {//PercentageRateDiscount case here
			if (Rate - Rate * RateDiscount / 100.0 < 0) {//ensuring it is not negative
				throw invalid_argument("Effective rate cannot be negative.");
			}
			return Rate - (Rate * RateDiscount / 100.0);
		}
	}
	//Get total price for Service class
	double GetTotalPrice() {
		if (Artifact::GetTotalPrice() + GetEffectiveRate() * Duration < 0) {
			throw invalid_argument("Total price cannot be negative.");
		}
		else {
			return Artifact::GetTotalPrice() + GetEffectiveRate() * Duration;
		}
	}


};

int main()
{

	vector<Division*> divisions;
	vector<Artifact*> artifacts;
	vector<Service*> services;

	// Create divisions objects
	divisions.push_back(new Division("D1", "Electronics", "0888 123456", "Handles electronic devices"));
	divisions.push_back(new Division("D2", "Furniture", "0888 654321", "Deals with home and office furniture"));
	divisions.push_back(new Division("D3", "Software", "0888 789123", "Provides IT solutions and software"));

	// Create artifacts objects
	artifacts.push_back(new Artifact("A1", "Laptop", "High-end gaming laptop", "Computers", divisions[0], 1200.0, 100.0, AmountDiscount, 10));
	artifacts.push_back(new Artifact("A2", "Office Chair", "Ergonomic chair", "Furniture", divisions[1], 150.0, 10.0, PercentageDiscount, 5));
	artifacts.push_back(new Artifact("A3", "Smartphone", "Latest model", "Phones", divisions[0], 800.0, 50.0, AmountDiscount, 8));

	// Create services objects
	services.push_back(new Service("S1", "Software Development", "Custom software development", "Software", divisions[2], 500.0, 50.0, PercentageDiscount, 1, 10.0, 20.0, 5.0, AmountRateDiscount));
	services.push_back(new Service("S2", "Laptop Repair", "Repair service for laptops", "Repair", divisions[0], 100.0, 20.0, AmountDiscount, 1, 2.0, 30.0, 10.0, PercentageRateDiscount));
	services.push_back(new Service("S3", "Furniture Assembly", "Assembly of furniture", "Furniture", divisions[1], 50.0, 5.0, PercentageDiscount, 1, 1.5, 25.0, 5.0, AmountRateDiscount));

	// Display artifact's Name and Total Price
	cout << "Artifacts:\n";
	for (Artifact* a : artifacts) {
		cout << a->GetName() << "  Total Price: $" << a->GetTotalPrice() << endl;
	}

	// Display service's Name and Total Price
	cout << "\nServices:\n";
	for (Service* s : services) {
		cout << s->GetName() << " - Total Price: $" << s->GetTotalPrice() << endl;
	}

	// Free the memory
	for (Division* d : divisions) delete d;
	for (Artifact* a : artifacts) delete a;
	for (Service* s : services) delete s;

	return 0;
}
