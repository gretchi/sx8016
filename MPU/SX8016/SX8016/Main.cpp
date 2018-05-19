#include "ClockGenerator.h"
#include "SX8016.h"

const char AA[] = R"(/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
/_      _____________  ___ ______ _______  _______  _______       /_
/_     /   _____/\   \/  //  __  \\   _  \ \   _  \ \   _  \      /_
/_     \_____  \  \     / >      </  /_\  \/  /_\  \/  /_\  \     /_
/_     /        \ /     \/   --   \  \_/   \  \_/   \  \_/   \    /_
/_    /_______  //___/\  \______  /\_____  /\_____  /\_____  /    /_
/_            \/       \_/      \/       \/       \/       \/     /_
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
/_ Y a m a m o o  M P U  E m u l a t o r  X  S e r i e s  8 0 0 0 /_
/_                                                                /_
/_        C O P Y R I G H T  S . Y A M A M U R A  2007.           /_
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_
)";


using namespace std;

int main()
{
	cout << AA << endl;

	ClockGenerator *clock = new ClockGenerator();
	Bus *bus = new Bus();
	SX8016 *sx8k = new SX8016(bus);
	


	unsigned __int64 i = 0;

	while (1) {
		clock->initClock();
		clock->generateClock(1);

		sx8k->clock();


		cout << fixed << setprecision(2) << clock->getDoubleClock() << "Hz\r";
		clock->confirmClock();

		i += 1;
	}

	
	// memory release
	delete(clock);
	delete(bus);
	delete(sx8k);


    return 0;
}


