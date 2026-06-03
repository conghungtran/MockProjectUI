#pragma once

#include <afx.h>  // For CObject
#include <iostream>
#include <string>
#include "PrinterConfig.h"

namespace PrinterHub {
    namespace Core {
        class Printer : public CObject {
            DECLARE_DYNAMIC(Printer)  // Thêm macro này

        public:
            std::string ID;
            std::string model;
            PrinterBrand brand;
            PrinterStatus status;
            std::string purchaseDate;
            int warrantyMonth;

        public:
            // Constructor
            Printer(std::string ID = ""
                ,std::string model = ""
                ,PrinterBrand brand = PrinterBrand::OTHER
                ,PrinterStatus status = PrinterStatus::ACTIVE
                ,std::string purchaseDate = ""
                ,int warrantyMonth = 12
            );

            // Destructor
            ~Printer();

            // Copy constructor & assignment
            Printer(const Printer& other);
            Printer& operator=(const Printer& other);

            // Operators
            bool operator==(const Printer& other) const;
            bool operator>(const Printer& other) const;
            friend std::ostream& operator<<(std::ostream& os, const Printer& p);

            // Getters
            std::string getId() const { return ID; }
            std::string getModel() const { return model; }
            PrinterBrand getBrand() const { return brand; }
            PrinterStatus getStatus() const { return status; }
            std::string getPurchaseDate() const { return purchaseDate; }
            int getWarrantyMonth() const { return warrantyMonth; }  // Sửa typo: getWarantyMonth → getWarrantyMonth

            // Setters (nên thêm)
            void setBrand(PrinterBrand b) { brand = b; }
            void setStatus(PrinterStatus s) { status = s; }
        };
    }
}