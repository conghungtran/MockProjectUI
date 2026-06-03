#include "pch.h"
#include "Printer.h"
#include <iostream>
using namespace PrinterHub::Core;

IMPLEMENT_DYNAMIC(Printer, CObject)

// Constructor
Printer::Printer(std::string ID
    , std::string model
    , PrinterBrand brand
    , PrinterStatus status
    , std::string purchaseDate
    , int warrantyMonth

    )
    : ID(ID)
    , model(model)
    , brand(brand)
    , status(status)
    , purchaseDate(purchaseDate)
    , warrantyMonth(warrantyMonth)
{
	std::cout << "Constructed Printer: " << *this << std::endl;
}

Printer::Printer() {}

// Destructor
Printer::~Printer()
{
}

// Copy constructor
Printer::Printer(const Printer& other)
    : ID(other.ID)
    , model(other.model)
    , brand(other.brand)
    , status(other.status)
    , purchaseDate(other.purchaseDate)
    , warrantyMonth(other.warrantyMonth)
{
}

// Assignment operator
Printer& Printer::operator=(const Printer& other)
{
    if (this != &other) {
        ID = other.ID;
        model = other.model;
        brand = other.brand;
        status = other.status;
        purchaseDate = other.purchaseDate;
        warrantyMonth = other.warrantyMonth;
    }
    return *this;
}

// Equality operator
bool Printer::operator==(const Printer& other) const
{
    return ID == other.ID;
}

// Greater than operator
bool Printer::operator>(const Printer& other) const
{
    return ID > other.ID;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Printer& p)
{
    os << "Printer{ID: " << p.ID
        << ", Model: " << p.model
        << ", Brand: " << (int)p.brand
        << ", Status: " << (int)p.status
        << ", PurchaseDate: " << p.purchaseDate
        << ", Warranty: " << p.warrantyMonth << " months}";
    return os;
}