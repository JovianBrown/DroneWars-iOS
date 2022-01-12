
#include "foldermanager.hpp"
#import <Foundation/Foundation.h>
#include "player.hpp"
#include <fstream>
#include <iostream>

using namespace fm;

FolderManager::FolderManager() {
    m_autoreleasePool = [[NSAutoreleasePool alloc] init];
}

FolderManager::~FolderManager() {
    [(NSAutoreleasePool *)m_autoreleasePool release];
}

const char * FolderManager::pathForDirectory(SearchPathDirectory directory, SearchPathDomainMask domainMask) {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSArray *URLs = [fileManager URLsForDirectory:(NSSearchPathDirectory)directory inDomains:domainMask];
    if (URLs.count == 0) return NULL;
    
    NSURL *URL = [URLs objectAtIndex:0];
    NSString *path = URL.path;
    
    // `fileSystemRepresentation` on an `NSString` gives a path suitable for POSIX APIs
    return path.fileSystemRepresentation;
}

const char * FolderManager::pathForDirectoryAppropriateForItemAtPath(SearchPathDirectory directory,
                                                                     SearchPathDomainMask domainMask, const char *itemPath, bool create) {
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *nsPath = [fileManager stringWithFileSystemRepresentation:itemPath length:strlen(itemPath)];
    NSURL *itemURL = (nsPath ? [NSURL fileURLWithPath:nsPath] : nil);
    
    NSURL *URL = [fileManager URLForDirectory:(NSSearchPathDirectory)directory
                                     inDomain:domainMask
                            appropriateForURL:itemURL
                                       create:create error:NULL];
    return URL.path.fileSystemRepresentation;
}
std::string FolderManager::loadGame()
{
    std::cout<<"Folder Manager Calling Load Game"<<std::endl;
    /// Define our default filemanager
    NSFileManager * fileManager = [NSFileManager defaultManager];
    /////Find our document directory
    NSURL * documentDirectory = [fileManager URLForDirectory:NSDocumentDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:NO error:nil];
  /// create an array to hold the list of documents in the directory documentDirectory
    NSArray * documentList = [fileManager contentsOfDirectoryAtURL:documentDirectory includingPropertiesForKeys:nil options:NSDirectoryEnumerationSkipsHiddenFiles error:nil];
    //// loop through the list of documents
 /*   for(NSURL * documentURL in documentList)
    {
        std::cout<<"Document Directory info: "<<std::endl;
        /// display content of each
        NSLog(@"%@",documentURL);
    }  */
    //////////
    
    
    
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *myPathDocs =  [documentsDirectory stringByAppendingPathComponent:@"playerstats.txt"];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:myPathDocs])
    {
        NSString *myPathInfo = [[NSBundle mainBundle] pathForResource:@"playerstats" ofType:@"txt"];
        NSFileManager *fileManager = [NSFileManager defaultManager];
        [fileManager copyItemAtPath:myPathInfo toPath:myPathDocs error:NULL];
    }
    
    //Load from File
    NSString *playerStats = [[NSString alloc] initWithContentsOfFile:myPathDocs encoding:NSUTF8StringEncoding error:NULL];
    //// print string to log
   // NSLog(@"%@",playerStats);
    ////convert NSstring to std::string
    std::string s_playerStats = std::string([playerStats UTF8String]);
    std::cout<<" Player stats string : "<<s_playerStats<<std::endl;
    return s_playerStats;
   
}
void FolderManager::saveGame(Player* player)
{
    std::cout<<"Folder Manager Calling Save Game"<<std::endl;

    /// get our default file manager
    NSFileManager * fileManager = [NSFileManager defaultManager];
    //// discover/ define the tempdirectory for saving player.txt
    NSString * tempDirectoryPath = NSTemporaryDirectory();
    //// convert the tempdirectory path to a usable URL for NSFM
    NSURL * tempDirectory = [NSURL fileURLWithPath:tempDirectoryPath];
    /////// below is our player content
    
    NSString * playerStats[12];  ///add 12th element 0 to maintain structure formed in separate function (load game)
    playerStats[0] = [NSString stringWithFormat:@"%d",player->getHps()];
    playerStats[1] = [NSString stringWithFormat:@"%d",player->getMaxHps()];
    playerStats[2] = [NSString stringWithFormat:@"%f",player->getMaxAcc()];
    playerStats[3] = [NSString stringWithFormat:@"%d",player->getMaxShield()];
    playerStats[4] = [NSString stringWithFormat:@"%d",player->getRareElements()];
    playerStats[5] = [NSString stringWithFormat:@"%d",player->getPreciousMetals()];
    playerStats[6] = [NSString stringWithFormat:@"%d",player->getEnergy()];
    playerStats[7] = [NSString stringWithFormat:@"%d",player->getLevel()];
    playerStats[8] = [NSString stringWithFormat:@"%d",player->getScore()];
    playerStats[9] = [NSString stringWithFormat:@"%d",player->getCredits()];
    playerStats[10] = [NSString stringWithFormat:@"%d",player->getCurrentWeapon()];
    playerStats[11] = [NSString stringWithFormat:@"0"];
  //  playerStats[10] = [NSString stringWithFormat:@"2"];
    ////// / player content end/ ///////
    //// array of our player content strings
    NSArray *playerStatsArray = [NSArray arrayWithObjects:playerStats count:12];
    ////// save to temp directory URL
    NSURL * saveURL  = [tempDirectory URLByAppendingPathComponent:[NSString stringWithFormat:@"player.txt"]];
    ////// create one long string out of array divided by a space.. maybe try \n ? ///
    NSString *playerStatsString = [playerStatsArray componentsJoinedByString:@" "];

    ///// finally write the string to the saveURL which is the tempdirectory
    [playerStatsString writeToURL:saveURL atomically:YES encoding:NSUTF8StringEncoding
                      error:nil];
  
    
    ////////////////////////////// End of writing to temp directory ///////////////
    
    /// choose a directory to list unhidden contents
   // NSArray * directoryList = [fileManager contentsOfDirectoryAtURL:tempDirectory includingPropertiesForKeys:nil options:NSDirectoryEnumerationSkipsHiddenFiles error:nil];
   
    //////////////////////// end of temp directory stufff //////////
    
    
    
    /// Lets find the document directory below////
    NSURL * documentDirectory = [fileManager URLForDirectory:NSDocumentDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:NO error:nil];
    /// Choose the player directory Documents/player
    NSURL * playerDirectory = [documentDirectory URLByAppendingPathComponent:@"player" isDirectory: YES];
    
    ////Create player Directory below
    [fileManager createDirectoryAtURL: playerDirectory withIntermediateDirectories:NO attributes:nil error:nil];
    // choose a filename for output
    NSString * fileName  = [NSString stringWithFormat:@"player.txt"];
    //// choose the directory/ file we are moving from
    NSURL * targetItem = [tempDirectory URLByAppendingPathComponent:fileName isDirectory: NO];
    // define the playerDirectory where we will move the player.txt file to
    playerDirectory = [playerDirectory URLByAppendingPathComponent:fileName isDirectory: NO];
    // finally move the file from target to playerDirectory
    [fileManager moveItemAtURL:targetItem toURL:playerDirectory error:nil];
    
    
    NSArray * documentList = [fileManager contentsOfDirectoryAtURL:documentDirectory includingPropertiesForKeys:nil options:NSDirectoryEnumerationSkipsHiddenFiles error:nil];

    for(NSURL * documentURL in documentList)
    {
        std::cout<<"Document Directory info: "<<std::endl;

        NSLog(@"%@",documentURL);
    }
    
    
    //// Finally write the file to the path
    
    NSString *documentsFolder = [NSHomeDirectory() stringByAppendingPathComponent:@"Documents"];
    NSString *fileName2 = [NSString stringWithString:@"playerstats.txt"];
    NSString *path = [documentsFolder stringByAppendingPathComponent:fileName2];
    
//    [[NSFileManager defaultManager] createFileAtPath:path contents:[playerStatsString dataUsingEncoding:NSUTF8StringEncoding] attributes:nil];
    [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
 [[NSFileManager defaultManager] createFileAtPath:path contents:[playerStatsString dataUsingEncoding:NSUTF8StringEncoding] attributes:nil];
   
}
