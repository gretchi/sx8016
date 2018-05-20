#include "ClockGenerator.h"
#include "SX8016.h"
#include "RAM.h"

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

void monitor(ClockGenerator *clock) {

	double accumulation_clock = 0.0;
	int i = 0;

	LARGE_INTEGER freq;

	while (1) {
		
		if (!isinf(clock->getDoubleClock()) && clock->getDoubleClock() != 0.0) {
			accumulation_clock += clock->getDoubleClock();
			Sleep(10);
			i++;
		}


		if (i == 10) {
			double avr_clock = accumulation_clock / (double) i;


			if (!isinf(avr_clock)) {
				QueryPerformanceFrequency(&freq);
				printf("Host CPU: %dMHz / SX8016: ", freq.LowPart / 1000);
				
				double unit_clock = avr_clock;
				string unit = "Hz";

				if (avr_clock > 1000000) {
					unit_clock = avr_clock / 1000000;
					unit = "MHz";

				}else if (avr_clock > 1000) {
					unit_clock = avr_clock / 1000;
					unit = "KHz";

				}
				
				cout << fixed << setprecision(2) << unit_clock << unit << "\r";
			}

			accumulation_clock = 0.0;
			i = 0;
		}
	}
}

int main()
{
	cout << AA << endl;

	ClockGenerator *clock = new ClockGenerator();
	clock->setCorrectionClock(true);

	Bus *bus = new Bus();
	Ram64k *ram = new Ram64k(bus, MAX_RAM_SIZE);
	SX8016 *sx8k = new SX8016(bus);

	auto mon = thread(monitor, clock);


	while (1) {
		clock->initClock();

		sx8k->clock();


		clock->generateClock(2249000);
		clock->confirmClock();

	}

	
	// memory release
	delete(clock);
	delete(bus);
	delete(sx8k);


    return 0;
}


