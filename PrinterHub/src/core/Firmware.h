// Firmware.h
#pragma once
#include <afx.h>
#include <string>
#include <unordered_map>

namespace PrinterHub {
    namespace Core {

        // ✅ Enum class cho Firmware Status
        enum class FirmwareStatus {
            Pending,        // Đang chờ xử lý
            Downloading,    // Đang tải về
            Verifying,      // Đang xác thực
            Updating,       // Đang cập nhật
            Completed,      // Hoàn thành
            Failed,         // Thất bại
            Cancelled,      // Đã hủy
            Paused          // Tạm dừng
        };

        // ✅ Class Firmware
        class Firmware {
        public:
            // Constructors
            Firmware();
            Firmware(const CString& strPrinterName,
                const CString& strFirmwareVersion,
                FirmwareStatus status = FirmwareStatus::Pending,
                const CString& strEstimatedTime = _T(""));

            ~Firmware();

            // Copy constructor & assignment
            Firmware(const Firmware& other);
            Firmware& operator=(const Firmware& other);

            // ========== Getters ==========
            int         getId() const { return m_id; }
            CString     getPrinterName() const { return m_strPrinterName; }
            CString     getFirmwareVersion() const { return m_strFirmwareVersion; }
            FirmwareStatus getStatus() const { return m_status; }
            CString     getEstimatedTime() const { return m_strEstimatedTime; }
            int         getProgress() const { return m_progress; }
            CString     getErrorMessage() const { return m_strErrorMessage; }
            COleDateTime getCreatedTime() const { return m_createdTime; }
            COleDateTime getCompletedTime() const { return m_completedTime; }

            // ========== Setters ==========
            void setId(int id) { m_id = id; }
            void setPrinterName(const CString& strName) { m_strPrinterName = strName; }
            void setFirmwareVersion(const CString& strVersion) { m_strFirmwareVersion = strVersion; }
            void setStatus(FirmwareStatus status) { m_status = status; }
            void setEstimatedTime(const CString& strTime) { m_strEstimatedTime = strTime; }
            void setProgress(int progress) { m_progress = progress; }
            void setErrorMessage(const CString& strError) { m_strErrorMessage = strError; }
            void setCompletedTime(COleDateTime time) { m_completedTime = time; }

            // ========== Helper methods ==========

            // Chuyển đổi Status ↔ String
            static CString StatusToString(FirmwareStatus status);
            static FirmwareStatus StringToStatus(const CString& strStatus);

            // Kiểm tra trạng thái
            bool isPending() const { return m_status == FirmwareStatus::Pending; }
            bool isCompleted() const { return m_status == FirmwareStatus::Completed; }
            bool isFailed() const { return m_status == FirmwareStatus::Failed; }
            bool isProcessing() const {
                return m_status == FirmwareStatus::Downloading ||
                    m_status == FirmwareStatus::Verifying ||
                    m_status == FirmwareStatus::Updating;
            }

            // Format hiển thị
            CString getDisplayText() const;
            COLORREF getStatusColor() const;

            // ========== Getters ==========
            CString GetReleaseDate() const { return m_rl_date; }
            CString GetDiskSpace() const { return diskpace; }

            // ========== Setters ==========
            void SetReleaseDate(const CString& date) { m_rl_date = date; }
            void SetDiskSpace(const CString& space) { diskpace = space; }

            // Hoặc setter với tham số là LPCTSTR (const TCHAR*)
            void SetReleaseDate(LPCTSTR date) { m_rl_date = date; }
            void SetDiskSpace(LPCTSTR space) { diskpace = space; }

        private:
            CString m_rl_date;
            CString diskpace;

            int m_id;
            CString m_strPrinterName;
            CString m_strFirmwareVersion;
            FirmwareStatus m_status;
            CString m_strEstimatedTime;
            int m_progress;
            CString m_strErrorMessage;
            COleDateTime m_createdTime;
            COleDateTime m_completedTime;

            static int s_nextId;
        };

        // ✅ Class FirmwareManager quản lý danh sách firmware jobs
        class FirmwareManager {
        public:
            FirmwareManager();
            ~FirmwareManager();

            // CRUD operations
            void addFirmware(const Firmware& firmware);
            void updateFirmware(int index, const Firmware& firmware);
            void removeFirmware(int index);
            void clearAll();

            // Query
            Firmware* getFirmware(int index);
            int getCount() const { return (int)m_firmwares.size(); }
            std::vector<Firmware>& getAllFirmwares() { return m_firmwares; }

            // Filter by status
            std::vector<Firmware> getByStatus(FirmwareStatus status) const;
            std::vector<Firmware> getPending() const;
            std::vector<Firmware> getProcessing() const;
            std::vector<Firmware> getCompleted() const;

            // Update status
            void updateStatus(int index, FirmwareStatus newStatus);
            void updateProgress(int index, int progress);

        private:
            std::vector<Firmware> m_firmwares;
        };

    }
}