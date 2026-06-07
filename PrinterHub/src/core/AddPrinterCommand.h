
// AddPrinterCommand.h
#pragma once
#include"ICommand.h"
#include "Printer.h"

namespace PrinterHub {
	namespace Core {
		class AddPrinterCommand : public ICommand {
		private:
			Printer m_printer;
		public:
			AddPrinterCommand(const Printer& p);
			void execute() override;
			void undo() override;
		};
	}
}