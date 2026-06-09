#pragma once
#include "IPrinterRepository.h"

namespace PrinterHub {
    namespace Core {
        class MockPrinterRepository : public IPrinterRepository {
        public:
            // Mock data
            std::vector<Printer> m_printers;
            bool m_loadCalled = false;
            bool m_saveCalled = false;
            int m_appendCount = 0;
            int m_updateCount = 0;
            int m_deleteCount = 0;

            bool Load(std::vector<Printer>& printers) override {
                std::cout << "Mock PrinterRepository::Load(): \n" << std::endl;
                m_loadCalled = true;
                printers = m_printers;
                return true;
            }

            bool Save(const std::vector<Printer>& printers) override {
                m_saveCalled = true;
                m_printers = printers;
                return true;
            }

            bool Append(const Printer& printer) override {
                m_appendCount++;
                m_printers.push_back(printer);
                return true;
            }

            bool Update(int index, const Printer& printer) override {
                m_updateCount++;
                if (index >= 0 && index < (int)m_printers.size()) {
                    m_printers[index] = printer;
                    return true;
                }
                return false;
            }

            bool Delete(int index) override {
                m_deleteCount++;
                if (index >= 0 && index < (int)m_printers.size()) {
                    m_printers.erase(m_printers.begin() + index);
                    return true;
                }
                return false;
            }

            std::string GetStoragePath() const override {
                return "mock://storage";
            }

            bool IsAvailable() const override {
                return true;
            }
        };
    }
}