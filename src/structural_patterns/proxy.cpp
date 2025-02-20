#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_set>

// Interface for file operations
class IFile {
public:
    virtual ~IFile() = default;

    // Opens the file
    virtual bool open() = 0;
    // Closes the file
    virtual bool close() = 0;
};

// RealFile represents the actual file object
class RealFile : public IFile {
public:
    // Constructor with filename
    explicit RealFile(const std::string& filename) : m_filename(filename) {}

    // Opens the file (simulated)
    bool open() override {
        std::cout << "Opening file: " << m_filename << "..." << std::endl;
        return true;
    }

    // Closes the file (simulated)
    bool close() override {
        std::cout << "Closing file: " << m_filename << "..." << std::endl;
        return true;
    }

private:
    std::string m_filename; // intrinsic state representing the file name
};

// FileProxy acts as a protective layer to control access to RealFile
class FileProxy : public IFile {
public:
    // Constructors with default user "default"
    FileProxy() : m_filename("default"), m_currentUser("default") {}
    explicit FileProxy(const std::string& filename) : m_filename(filename), m_currentUser("default") {}
    FileProxy(const std::string& filename, const std::string& username)
        : m_filename(filename), m_currentUser(username) {}

    ~FileProxy() = default;

    // Sets the current user accessing the file
    void setCurrentUser(const std::string& username) {
        m_currentUser = username;
    }

    // Adds a user to the access list
    bool addUserToAccessList(const std::string& username) {
        // If the user already has access, nothing to add
        if (checkIfUserHasAccess(username)) {
            return true;
        }
        m_usersWithAccess.insert(username);
        return true;
    }

    // Checks if a user has access
    bool checkIfUserHasAccess(const std::string& username) const {
        return m_usersWithAccess.find(username) != m_usersWithAccess.end();
    }

    // Opens the file if the current user has access; creates the RealFile if needed
    bool open() override {
        if (!checkIfUserHasAccess(m_currentUser)) {
            std::cerr << "Access denied: " << m_currentUser 
                      << " does not have permission to open this file!" << std::endl;
            return false;
        }

        // Deferred initialization: create the RealFile only when needed
        if (!m_file) {
            m_file = std::make_unique<RealFile>(m_filename);
        }
        return m_file->open();
    }

    // Closes the file if it was opened
    bool close() override {
        if (m_file) {
            return m_file->close();
        }
        std::cerr << "No file instance to close!" << std::endl;
        return false;
    }

private:
    std::string m_filename;         // File name to be opened
    std::unordered_set<std::string> m_usersWithAccess;  // Set of users with access
    std::string m_currentUser;      // The user currently trying to access the file
    std::unique_ptr<IFile> m_file;  // Deferred initialization of the real file
};

int main() {
    try {
        // Create a FileProxy for "logs.txt" with current user "user123"
        auto logsFile = std::make_unique<FileProxy>("logs.txt", "user123");

        // Grant access to "user123"
        logsFile->addUserToAccessList("user123");

        // Attempt to open the file
        if (logsFile->open()) {
            // File opened successfully; now close it.
            logsFile->close();
        }
    } catch (const std::exception& error) {
        std::cout << "Exception: " << error.what() << std::endl;
    }

    return 0;
}
