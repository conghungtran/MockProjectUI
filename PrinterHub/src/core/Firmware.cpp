// Firmware.cpp
#include "pch.h"
#include "Firmware.h"
#include <map>

namespace PrinterHub {
    namespace Core {

        // Static member initialization
        int Firmware::s_nextId = 1;

        // ============================================
        // FIRMWARE CLASS IMPLEMENTATION
        // ============================================

        Firmware::Firmware()
            : m_id(s_nextId++)
            , m_status(FirmwareStatus::Pending)
            , m_progress(0)
        {
            m_createdTime = COleDateTime::GetCurrentTime();
        }

        Firmware::Firmware(const CString& strPrinterName,
            const CString& strFirmwareVersion,
            FirmwareStatus status,
            const CString& strEstimatedTime)
            : m_id(s_nextId++)
            , m_strPrinterName(strPrinterName)
            , m_strFirmwareVersion(strFirmwareVersion)
            , m_status(status)
            , m_strEstimatedTime(strEstimatedTime)
            , m_progress(0)
        {
            m_createdTime = COleDateTime::GetCurrentTime();
        }

        Firmware::~Firmware()
        {
        }

        Firmware::Firmware(const Firmware& other)
            : m_id(other.m_id)
            , m_strPrinterName(other.m_strPrinterName)
            , m_strFirmwareVersion(other.m_strFirmwareVersion)
            , m_status(other.m_status)
            , m_strEstimatedTime(other.m_strEstimatedTime)
            , m_progress(other.m_progress)
            , m_strErrorMessage(other.m_strErrorMessage)
            , m_createdTime(other.m_createdTime)
            , m_completedTime(other.m_completedTime)
        {
        }

        Firmware& Firmware::operator=(const Firmware& other)
        {
            if (this != &other) {
                m_id = other.m_id;
                m_strPrinterName = other.m_strPrinterName;
                m_strFirmwareVersion = other.m_strFirmwareVersion;
                m_status = other.m_status;
                m_strEstimatedTime = other.m_strEstimatedTime;
                m_progress = other.m_progress;
                m_strErrorMessage = other.m_strErrorMessage;
                m_createdTime = other.m_createdTime;
                m_completedTime = other.m_completedTime;
            }
            return *this;
        }

        // ✅ Chuyển đổi FirmwareStatus → CString
        CString Firmware::StatusToString(FirmwareStatus status)
        {
            static const std::unordered_map<FirmwareStatus, CString> statusMap = {
                {FirmwareStatus::Pending,    _T("Pending")},
                {FirmwareStatus::Downloading, _T("Downloading")},
                {FirmwareStatus::Verifying,  _T("Verifying")},
                {FirmwareStatus::Updating,   _T("Updating")},
                {FirmwareStatus::Completed,  _T("Completed")},
                {FirmwareStatus::Failed,     _T("Failed")},
                {FirmwareStatus::Cancelled,  _T("Cancelled")},
                {FirmwareStatus::Paused,     _T("Paused")}
            };

            auto it = statusMap.find(status);
            return (it != statusMap.end()) ? it->second : _T("Unknown");
        }

        // ✅ Chuyển đổi CString → FirmwareStatus
        FirmwareStatus Firmware::StringToStatus(const CString& strStatus)
        {
            static const std::unordered_map<CString, FirmwareStatus> stringMap = {
                {_T("Pending"),     FirmwareStatus::Pending},
                {_T("Downloading"), FirmwareStatus::Downloading},
                {_T("Verifying"),   FirmwareStatus::Verifying},
                {_T("Updating"),    FirmwareStatus::Updating},
                {_T("Completed"),   FirmwareStatus::Completed},
                {_T("Failed"),      FirmwareStatus::Failed},
                {_T("Cancelled"),   FirmwareStatus::Cancelled},
                {_T("Paused"),      FirmwareStatus::Paused}
            };

            auto it = stringMap.find(strStatus);
            return (it != stringMap.end()) ? it->second : FirmwareStatus::Pending;
        }

        CString Firmware::getDisplayText() const
        {
            CString strDisplay;
            strDisplay.Format(_T("%s - %s [%s]"),
                m_strPrinterName,
                m_strFirmwareVersion,
                StatusToString(m_status));
            return strDisplay;
        }

        //COLORREF Firmware::getStatusColor() const
        //{
        //    switch (m_status) {
        //    case FirmwareStatus::Pending:    return RGB(255, 193, 7);   // Vàng
        //    case FirmwareStatus::Downloading: return RGB(0, 120, 215);   // Xanh dương
        //    case FirmwareStatus::Verifying:  return RGB(0, 120, 215);    // Xanh dương
        //    case FirmwareStatus::Updating:   return RGB(0, 120, 215);    // Xanh dương
        //    case FirmwareStatus::Completed:  return RGB(40, 167, 69);    // Xanh lá
        //    case FirmwareStatus::Failed:     return RGB(220, 53, 69);    // Đỏ
        //    case FirmwareStatus::Cancelled:  return RGB(108, 117, 125);  // Xám
        //    case FirmwareStatus::Paused:     return RGB(255, 193, 7);    // Vàng
        //    default: return RGB(0, 0, 0);
        //    }
        //}

        // ============================================
        // FIRMWARE MANAGER IMPLEMENTATION
        // ============================================

        FirmwareManager::FirmwareManager()
        {
        }

        FirmwareManager::~FirmwareManager()
        {
        }

        void FirmwareManager::addFirmware(const Firmware& firmware)
        {
            m_firmwares.push_back(firmware);
        }

        void FirmwareManager::updateFirmware(int index, const Firmware& firmware)
        {
            if (index >= 0 && index < (int)m_firmwares.size()) {
                m_firmwares[index] = firmware;
            }
        }

        void FirmwareManager::removeFirmware(int index)
        {
            if (index >= 0 && index < (int)m_firmwares.size()) {
                m_firmwares.erase(m_firmwares.begin() + index);
            }
        }

        void FirmwareManager::clearAll()
        {
            m_firmwares.clear();
        }

        Firmware* FirmwareManager::getFirmware(int index)
        {
            if (index >= 0 && index < (int)m_firmwares.size()) {
                return &m_firmwares[index];
            }
            return nullptr;
        }

        std::vector<Firmware> FirmwareManager::getByStatus(FirmwareStatus status) const
        {
            std::vector<Firmware> result;
            for (const auto& fw : m_firmwares) {
                if (fw.getStatus() == status) {
                    result.push_back(fw);
                }
            }
            return result;
        }

        std::vector<Firmware> FirmwareManager::getPending() const
        {
            return getByStatus(FirmwareStatus::Pending);
        }

        std::vector<Firmware> FirmwareManager::getProcessing() const
        {
            std::vector<Firmware> result;
            for (const auto& fw : m_firmwares) {
                if (fw.isProcessing()) {
                    result.push_back(fw);
                }
            }
            return result;
        }

        std::vector<Firmware> FirmwareManager::getCompleted() const
        {
            return getByStatus(FirmwareStatus::Completed);
        }

        void FirmwareManager::updateStatus(int index, FirmwareStatus newStatus)
        {
            if (index >= 0 && index < (int)m_firmwares.size()) {
                m_firmwares[index].setStatus(newStatus);
                if (newStatus == FirmwareStatus::Completed) {
                    m_firmwares[index].setCompletedTime(COleDateTime::GetCurrentTime());
                }
            }
        }

        void FirmwareManager::updateProgress(int index, int progress)
        {
            if (index >= 0 && index < (int)m_firmwares.size()) {
                m_firmwares[index].setProgress(progress);
            }
        }

    }
}