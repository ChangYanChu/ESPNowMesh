/**
 * SerialTerminal.h - Serial Command Interface for ESPNowMesh
 * 
 * This class provides a consistent interface for processing serial commands
 * in ESPNowMesh applications. It offers standard built-in commands
 * for controlling mesh network operations from the serial monitor.
 */

#ifndef SERIAL_TERMINAL_H
#define SERIAL_TERMINAL_H

#include <Arduino.h>
#include "ESPNowMesh.h"
#include <vector>

// Define command callback function type
typedef void (*CommandCallback)(const String& args);

// Structure to hold custom command information
struct CustomCommand {
    String name;
    String description;
    CommandCallback callback;
};

class SerialTerminal {
public:
    // Constructor
    SerialTerminal(ESPNowMesh& meshInstance, Stream& serial = Serial);
    
    // Process any available serial input (call this in loop)
    void process();
    
    // Configuration
    void setCommandPrefix(char prefix);
    void enableEcho(bool enable);
    void enablePrompt(bool enable);
    void setPrompt(const String& prompt);
    
    // Custom command management
    void addCommand(const String& name, const String& description, CommandCallback callback);
    void removeCommand(const String& name);
    void clearCustomCommands();
    
    // Print help and status information
    void printHelp();
    void printStatus();
    
private:
    ESPNowMesh& mesh;
    Stream& serial;
    char commandPrefix = '/';
    bool echoEnabled = true;
    bool promptEnabled = true;
    String prompt = "> ";
    uint8_t defaultTTL = MESH_TTL_DEFAULT;
    
    // Command buffer
    String commandBuffer;
    bool processingCommand = false;
    
    // Custom commands storage
    std::vector<CustomCommand> customCommands;
    
    // Internal command handlers
    void handleCommand(String cmd);
    
    // Standard command handlers
    void cmdDiscovery();
    void cmdListNeighbors();
    void cmdBroadcast(const String& msg);
    void cmdUnicast(const String& args);
    void cmdReliable(const String& args); // New reliable send method
    void cmdSetRole(const String& role);
    void cmdSetTTL(const String& ttlStr);
    void cmdDebug(const String& mode);
    void cmdPing();
    
    // Helper functions
    void printMac(const uint8_t* mac);
    bool macStringToBytes(const String& macStr, uint8_t* targetMac);
};

#endif // SERIAL_TERMINAL_H