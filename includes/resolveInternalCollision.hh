#define AC 4
#define MAXSTAGE 5

int resolveInternalCollision(std::array<double,AC> &counters, std::array<int,AC> &backlogg, std::array<int,AC> &stickiness, 
	std::array<int,AC> &stages, std::array<int,AC> &recomputeBackoff, std::array<double,AC> &totalInternalACCol,
	std::array<int,AC> &retAttemptAC){

	int iterator = counters.size() - 1;
	int acToTx;
	int winner = -1;

	recomputeBackoff.fill(0);

	// cout << "Internal collision check" << endl;
	// for (int i = 0; i < AC; i++)
	// {
	// 	cout << "\tAC " << i << ": " << counters.at(i) <<  endl;
	// }

	for(int i = iterator; i >= 0; i--)
	{
		if(backlogg.at(i) == 1)
		{ 
			if(counters.at(i) == 0) 
			{
				winner = i; 
				break;
			}
		}
	}

	// cout << "\tWinner AC " << winner << endl;

	acToTx = winner;

	for (int i = 0; i < (AC -1); i++)
	{
		for (int j = i+1; j < AC; j++)
		{
			if( (backlogg.at(i) == 1) && (backlogg.at(j) == 1))
			{
				if(counters.at(i) == counters.at(j))
				{	
					int recompute = std::min(i,j);
					recomputeBackoff.at(recompute) = 1;
					//stickiness.at(recompute) = std::max((int) stickiness.at(recompute) - 1, 0);
					//stages.at(recompute) = std::min((int)stages.at(recompute) + 1, MAXSTAGE);

					// cout << "\nInternal collision" << endl;
					// cout << "---AC " << i << " timer: " << counters.at(i) << ". AC " << j << " timer: " << counters.at(j) <<  endl;
					// cout << "\t---Changing " << recompute << endl;

					totalInternalACCol.at(recompute)++;
					//retAttemptAC.at(recompute)++;
				}
			}
		}
	}

	return(acToTx);
	
}