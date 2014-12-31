# setwd("file:///home/solvek/projects/electronics/counter/data")
# source("../plotchart.R")

# File with data
filepath = "data.csv"
# Start date
startDate = '2014-12-26 12:00:15'

# End date
endDate = '2014-12-26 20:08:14'

# Period in seconds
period = 600

nsd = as.numeric(as.POSIXlt(startDate))
ned = as.numeric(as.POSIXlt(endDate))

items = seq(nsd, ned, by=period)
series = read.csv(filepath, header=FALSE, col.names=c("time", "value"))

bars = 
	sapply(items, function(x){
		length(subset(series, time/1000>=x & time/1000<(x+period))$value)
	})

barplot(bars, names.arg = as.POSIXlt(items, origin="1970-01-01"))