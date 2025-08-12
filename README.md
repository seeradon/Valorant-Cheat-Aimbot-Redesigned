# Valorant Cheat Aimbot 

This project includes an aimbot designed to be used in the Valorant game, providing players with enhanced precision in aiming.

**Warning: Do Not Try This Software on Your Own Main Accounts. If you try, I would like to state that all responsibility is on you.**

## How to use

1. Copy the project to your computer or download it as a ZIP file.
2. Compile the project.
3. Start the Valorant game.
4. Run the compiled file in the project folder to run the cheat:

   ``bash
   ./64x
   ```

## Features

- **Wallhack (ESP):** The aimbot provides a wallhack feature, allowing you to see enemies through walls.
- **Health Bar Display:** The aimbot displays the health bar of enemies, providing information about their health status.
- **Distance Indicator:** Shows the distance between you and the targeted enemy.
- **Customizable Settings:** The aimbot includes customizable settings to adjust features according to user preferences. (F6)


## Example Use

When the project is started, the aimbot will run automatically. You can switch the aimbot on and off with the F6 key.

```cpp
#include <iostream>

int main()
{
	fProcess.RunProcess();
	cout << "Game found! Running aimbot." << endl;

	while (!GetAsyncKeyState(F6_Key))
	{
		MyPlayer.ReadInformation();
		Aimbot();
	}
}
```

## Development Environment

You can use a C++ IDE such as [Visual Studio Code](https://code.visualstudio.com/) or [Code::Blocks](http://www.codeblocks.org/) to develop and customize this project.

## Known Issues

- The usage of the aimbot may violate the terms of use of Valorant.
- Regular updates and maintenance of the aimbot may not be guaranteed.

## License

This project is open source and licensed under the MIT license. For more information, see the [LICENSE](LICENSE) file.

**Warning: Any responsibility arising from the use of this project is the user's own.**