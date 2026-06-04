#pragma once

#include <afx.h>  // For CObject
#include <iostream>
#include <string>
#include "PrinterConfig.h"

namespace PrinterHub {
    namespace Core {
        class Printer : public CObject {
            DECLARE_DYNAMIC(Printer)  // Thêm macro này

        private:
            std::string ID;
            std::string model;
            PrinterBrand brand;
            PrinterStatus status;
            std::string purchaseDate;
            int warrantyMonth;

        public:
            // Constructor
            Printer(std::string ID = ""
                , std::string model = ""
                , PrinterBrand brand = PrinterBrand::OTHER
                , PrinterStatus status = PrinterStatus::ACTIVE
                , std::string purchaseDate = ""
                , int warrantyMonth = 12
            );

            // Destructor
            ~Printer();

            // Copy constructor & assignment
            Printer(const Printer& other);
            Printer& operator=(const Printer& other);
            // Move operator
            Printer& operator=(Printer&& other) noexcept
            {
                if (this != &other)
                {
                    // ✅ CHỈ GIỮ LẠI ID
                    std::string oldId = this->ID;

                    // Copy các field khác từ other
                    this->model = std::move(other.model);
                    this->brand = other.brand;
                    this->status = other.status;
                    this->purchaseDate = std::move(other.purchaseDate);
                    this->warrantyMonth = other.warrantyMonth;

                    // KHÔNG copy ID, giữ nguyên ID cũ
                    this->ID = oldId;
                }
                return *this;
            }


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


            // ✅ Setters (thêm mới)
            void setId(const std::string& id) { ID = id; }
            void setModel(const std::string& mdl) { model = mdl; }
            void setBrand(PrinterBrand b) { brand = b; }
            void setStatus(PrinterStatus s) { status = s; }
            void setPurchaseDate(const std::string& date) { purchaseDate = date; }
            void setWarrantyMonth(int months) { warrantyMonth = months; }

            // Hoặc gộp lại cho tiện
            void setAll(const std::string& mdl,
                PrinterBrand b, PrinterStatus s,
                const std::string& date, int months);
        };
    }
}