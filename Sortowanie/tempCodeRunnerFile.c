				d->month = 0;
				d->year++;
			}
			d->day = days - (month_days - d->day);
			days = 0;
		}
		else
		{
			d->day += days;
			days = 0;
		}
	}