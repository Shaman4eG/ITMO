function sleep(ms) {
	return new Promise(resolve => setTimeout(resolve, ms));
}

async function showTime()
{
		var time = document.getElementById( "time" );
		
		var currentDate
		var day 
		var month 
		var year
		
		while (true)
		{
			currentDate = new Date()
			day = currentDate.getDate()
			month = currentDate.getMonth() + 1
			year = currentDate.getFullYear()

			if (day < 10) day = "0" + day
			
			
			time.innerHTML = day + "/" + month + "/" + year + " " + new Date().toLocaleTimeString();
			
			await sleep(11000);
		}
}