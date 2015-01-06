# setwd("/home/solvek/projects/electronics/data")
# source("../meteostation2/plotchart.R")

# File with data
filepath = "data.csv"
# Start date
startDate = '2015-01-05 00:00:00'

# End date
endDate = '2015-01-05 23:00:00'

nsd = as.numeric(as.POSIXlt(startDate))
ned = as.numeric(as.POSIXlt(endDate))

series = read.csv(filepath, header=FALSE, col.names=c("time", "signal", "temperature", "humidity"))

selected = subset(series, time/1000>=nsd & time/1000<ned)

f <- rep(1/20, 20)
y <- filter(selected$signal, f, sides=1)

plot(x=as.POSIXlt(selected$time/1000, origin="1970-01-01"), y=y, type="l", col="blue", ann=FALSE)