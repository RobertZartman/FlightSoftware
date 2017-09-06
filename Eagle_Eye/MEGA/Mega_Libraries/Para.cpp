/**
 * Para.cpp handels the enablement/deployment of the parachute
 *    onboard the Eagle Eye Craft.
 */


#include "Para.h"


/**
 * Assigns correct pin to connect to the Parachute's Relay.
 */
void Para::Para_Initialize()
{
	//Sets the pin RELAY1 to LOW to induce a open circuit therfore preventing a premature deployment
	//  in the next line of code.
	digitalWrite(RELAY1, LOW);
	
	//Assigns RELAY1 as the output communication pin to the Parachute.
	pinMode(RELAY1, OUTPUT);
	Serial.println("Parachute Online.");
}


/**
 * Primary purpose is passively be aware of the crafts situation, altitude, and orientation 
 *    and arm/deploy the parachute at the right conditions.
 */
void Para::Para_Manager()
{
	//Passively observes the change in altitude and when above a cset altitude, ENABLES the chute.
	if (!chute_enable && data.Altitude >= PARACHUTE_ARM_HEIGHT) {  
		
		//Counter used to make sure the craft stays above the arm height for a certain amount of time before it 
		//   arms. Purpose is to prevent the craft rising just above the height and arming and than dropping below
		//   and deploying while the craft is still going up. (would cause problems)
		saftey_counter++;
		
		//Checks for the saftey counter described above to reach a certain amount.
		if (saftey_counter >= 4) {
			
			//ENABLES the parachute.
			chute_enable = true;
			Serial.print("ENABLED: "); Serial.print(data.Altitude); Serial.println(" meters ");
			
			//Assigned the Mega Event to reflect the chute being ENABLED.
			data.ME = 1;
		}
		
		//Checks for the craft to drop below the required enable height.
		else if (data.Altitude <= PARACHUTE_ARM_HEIGHT) {
			
			//Resets saftey counter to 0. 
			saftey_counter = 0;
			Serial.println("Saftey reset to 0.");
			
			//Assigned the Mega Event to reflect the chute being DISABLED.
			data.ME = 0;
		}
	}
	
	//Passively observes the change in altitude and when dropping below a set altitude, DEPLOYS the parachute.
	if (!chute_deploy && chute_enable && data.Altitude <= PARACHUTE_DEPLOY_HEIGHT) {
		
		
		//Closes the circuit, therefore providing power to the deploy the parachute.
		digitalWrite(RELAY1, HIGH);
		chute_deploy = true;
		
		//Assigns the Mega Event to reflect the chute being DEPLOYED.
		data.ME = 2;
		
		
		Serial.print("DEPLOYED: "); Serial.print(data.Altitude); Serial.println(" meters");
		
		
		//Provides power for 2 seconds. Than cuts power and opens the circuit.
		delay(2000);
		digitalWrite(RELAY1, LOW);
	}
}


/**
 * Checks to see if the craft is in the right orientation to deploy.
 */
bool RedZone()
{
	return !(data.Roll >= 135 && data.Pitch <= 45);
}