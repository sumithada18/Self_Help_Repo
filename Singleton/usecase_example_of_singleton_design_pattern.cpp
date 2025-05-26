/*
Minimalist Real Industry Use-Case Example: Application Configuration Manager

Scenario:
Imagine you're building a desktop application. This application needs to store and retrieve user preferences or application settings, like:
• Theme (dark mode/light mode)
• Default font size
• API key for an online service
These settings are usually stored in a configuration file (e.g., settings.json, config.ini).

Problem without Singleton:
If every part of your application (e.g., the UI rendering part, the network communication part, the text editor part) independently tried to read this configuration file, you'd have:
1. Redundant Work: The file might be read multiple times, which is inefficient.
2. Inconsistent State: What if one part reads the file, then another part modifies it and re-reads it, while the first part still has the old values?
3. Complexity: Passing around configuration data to every component that needs it would be cumbersome.

How Singleton Solves It (Conceptual):

You create a ConfigurationManager class as a Singleton.
*/

// ---- Conceptual (not actual code, just to illustrate) ----
class ConfigurationManager {
private:
    // Private constructor: Only ConfigurationManager can create itself
    ConfigurationManager() {
        // Load settings from "settings.json" ONCE here
        // Store them in private member variables (e.g., theme, fontSize)
    }

    // Static member to hold the single instance
    static ConfigurationManager* instance;

    // Actual settings data
    string theme;
    int fontSize;
    string apiKey;

public:
    // Static method to get the instance
    static ConfigurationManager* getInstance() {
        if (instance == nullptr) {
            instance = new ConfigurationManager(); // Creates the instance if it doesn't exist
        }
        return instance; // Returns the single, shared instance
    }

    // Public methods to get specific settings
    string getTheme() { return theme; }
    int getFontSize() { return fontSize; }
    string getApiKey() { return apiKey; }

    // (Maybe methods to save settings, etc.)
};

// Initialize static member
ConfigurationManager* ConfigurationManager::instance = nullptr;
// ---- End Conceptual ----

/*
Explanation and Key Parts:
1. ConfigurationManager Class:
◦ Private Constructor (ConfigurationManager()): Prevents direct instantiation from outside the class. It's called only once by getInstance(). This is where you'd typically load settings from a file.
◦ Deleted Copy/Move Operations: ConfigurationManager(const ConfigurationManager&) = delete; etc., explicitly prevent copying or moving the singleton instance, further enforcing its uniqueness.
◦ Private Data Members (theme, fontSize, apiKey): Hold the actual configuration data.
◦ Public getInstance() (Meyers' Singleton - Preferred):
  ▪ static ConfigurationManager& getInstance(): This is the public access point.
  ▪ static ConfigurationManager instance;: This is the core of the Meyers' Singleton. The static keyword here means:
    ▪ It's initialized only once, the first time getInstance() is called.
    ▪ C++11 and later standards guarantee that this initialization is thread-safe. You don't need to add manual locks for this specific pattern.
  ▪ return instance;: Returns a reference to the single, static instance.
◦ Public Getter/Setter Methods (getTheme, setTheme, etc.): Provide controlled access to the configuration data.

2. main() Function (Usage):
◦ ConfigurationManager& config1 = ConfigurationManager::getInstance();: Gets the singleton instance. If it's the first call, the ConfigurationManager constructor runs.
◦ ConfigurationManager& config2 = ConfigurationManager::getInstance();: Gets the same instance again. The constructor does not run again.
◦ The if (&config1 == &config2) check proves that both references point to the exact same object in memory.
◦ Changes made via config1 (e.g., config1.setTheme("light");) are visible when accessing via config2 because they are the same object.
  */
