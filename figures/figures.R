#######################################################
#  Example Script for Running 'CareCascade' Analysis  #
#                 Author: Jack Olney                  #
#                  Copyright, 2015                    #
#       Contact: jack.olney11@imperial.ac.uk          #
#######################################################

# Clear the console
rm(list=ls())

# Set the current directory to somewhere where the results of running './scripts/control.py' has deposited all the resulting simulation files.
setwd("/path/")

# Create an output plot folder
system("mkdir ./plots")


# Set up run and intervention vectors
run <- c("run1","run2","run3","run4","run5","run6","run7","run8","run9","run10")
interventions <- c("Baseline", "Hbct_1", "Hbct_2", "Vct_1", "Vct_2", "HbctPocCd4_1", "HbctPocCd4_2", "Linkage_1", "Linkage_2", "VctPocCd4", "PreOutreach_1", "PreOutreach_2", "ImprovedCare_1", "ImprovedCare_2", "PocCd4", "ArtOutreach_1", "ArtOutreach_2", "Adherence_1", "Adherence_2", "ImmediateArt", "UniversalTestAndTreat_1", "UniversalTestAndTreat_2")

# These loops take each intervention, runs through all available repeat simulations (run1 to run10) and then computes the mean of all results.
# Load initial baseline results
if(file.exists(gsub(" ","",paste("./",run[1],"/output/",interventions[1],"/currentWorkspace.RData"))))
    load(gsub(" ","",paste("./",run[1],"/output/",interventions[1],"/currentWorkspace.RData"))) else stop("File (run1:baseline) does not exist.")

# Loop through all interventions and runs and dynamically average them (allows for missing runs)
for(i in 1:length(interventions)) {
    cat(paste("",interventions[i], "\n"))
    # Create vector of names
    outputNames <- c()
    for(m in 1:length(Baseline))
        outputNames[m] <- names(Baseline)[m]
    # Create list
    output <- sapply(outputNames,function(x) NULL)
    for(n in 1:length(output))
        output[[n]] <- vector('double',length(Baseline[[n]]))
    theLength = 0
    for(j in 1:length(run)) {
        if(file.exists(gsub(" ","",paste("./",run[j],"/output/",interventions[i],"/currentWorkspace.RData")))) {
            load(gsub(" ","",paste("./",run[j],"/output/",interventions[i],"/currentWorkspace.RData")))
            cat(paste("\t",run[j], "\n"))
            theLength <- theLength + 1
            for(k in 1:length(Baseline)) {
                output[[k]] <- output[[k]] + get(interventions[i])[[k]]
            }
        }
    }
    cat(paste("\t\t\ttheLength =",theLength, "\n"))
    for(l in 1:length(Baseline)) {
        output[[l]] <- output[[l]] / theLength
    }
    assign(interventions[i],output)
}
print("\tComplete!")


# sizeAdjustment
# Set to the same value as popSize e.g. 10 (as used in manuscript)
sizeAdjustment = 10


#####################
# PLOTS AND FIGURES #
#####################

library(RColorBrewer)
p <- brewer.pal(12,"Set3")
d <- brewer.pal(12,"Paired")
R <-brewer.pal(9,"Reds")
O <- brewer.pal(9,"Oranges")
G <-brewer.pal(9,"Greens")
B <-brewer.pal(9,"Blues")
plotCol <- c(R[7],R[5],O[6],p[6],O[3],G[7],p[7],G[3],B[7],B[5],d[10],d[9])

# Create 'DALYs averted' calculation array
resultDALY <- matrix(0,2,12)
resultDALY[1,1] <- (sum(Baseline$sDALY) - sum(Hbct_1$sDALY)) * sizeAdjustment
resultDALY[2,1] <- (sum(Baseline$sDALY) - sum(Hbct_2$sDALY)) * sizeAdjustment
resultDALY[1,2] <- (sum(Baseline$sDALY) - sum(Vct_1$sDALY)) * sizeAdjustment
resultDALY[2,2] <- (sum(Baseline$sDALY) - sum(Vct_2$sDALY)) * sizeAdjustment
resultDALY[1,3] <- (sum(Baseline$sDALY) - sum(HbctPocCd4_1$sDALY)) * sizeAdjustment
resultDALY[2,3] <- (sum(Baseline$sDALY) - sum(HbctPocCd4_2$sDALY)) * sizeAdjustment
resultDALY[1,4] <- (sum(Baseline$sDALY) - sum(Linkage_1$sDALY)) * sizeAdjustment
resultDALY[2,4] <- (sum(Baseline$sDALY) - sum(Linkage_2$sDALY)) * sizeAdjustment
resultDALY[1,5] <- (sum(Baseline$sDALY) - sum(VctPocCd4$sDALY)) * sizeAdjustment
resultDALY[1,6] <- (sum(Baseline$sDALY) - sum(PreOutreach_1$sDALY)) * sizeAdjustment
resultDALY[2,6] <- (sum(Baseline$sDALY) - sum(PreOutreach_2$sDALY)) * sizeAdjustment
resultDALY[1,7] <- (sum(Baseline$sDALY) - sum(ImprovedCare_1$sDALY)) * sizeAdjustment
resultDALY[2,7] <- (sum(Baseline$sDALY) - sum(ImprovedCare_2$sDALY)) * sizeAdjustment
resultDALY[1,8] <- (sum(Baseline$sDALY) - sum(PocCd4$sDALY)) * sizeAdjustment
resultDALY[1,9] <- (sum(Baseline$sDALY) - sum(ArtOutreach_1$sDALY)) * sizeAdjustment
resultDALY[2,9] <- (sum(Baseline$sDALY) - sum(ArtOutreach_2$sDALY)) * sizeAdjustment
resultDALY[1,10] <- (sum(Baseline$sDALY) - sum(Adherence_1$sDALY)) * sizeAdjustment
resultDALY[2,10] <- (sum(Baseline$sDALY) - sum(Adherence_2$sDALY)) * sizeAdjustment
resultDALY[1,11] <- (sum(Baseline$sDALY) - sum(ImmediateArt$sDALY)) * sizeAdjustment
resultDALY[1,12] <- (sum(Baseline$sDALY) - sum(UniversalTestAndTreat_1$sDALY)) * sizeAdjustment
resultDALY[2,12] <- (sum(Baseline$sDALY) - sum(UniversalTestAndTreat_2$sDALY)) * sizeAdjustment

# Create 'Additional COST of care' calculation array
resultCOST <- matrix(0,2,12)
resultCOST[1,1] <- (sum(Hbct_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,1] <- (sum(Hbct_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,2] <- (sum(Vct_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,2] <- (sum(Vct_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,3] <- (sum(HbctPocCd4_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,3] <- (sum(HbctPocCd4_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,4] <- (sum(Linkage_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,4] <- (sum(Linkage_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,5] <- (sum(VctPocCd4$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,6] <- (sum(PreOutreach_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,6] <- (sum(PreOutreach_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,7] <- (sum(ImprovedCare_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,7] <- (sum(ImprovedCare_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,8] <- (sum(PocCd4$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,9] <- (sum(ArtOutreach_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,9] <- (sum(ArtOutreach_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,10] <- (sum(Adherence_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,10] <- (sum(Adherence_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,11] <- (sum(ImmediateArt$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[1,12] <- (sum(UniversalTestAndTreat_1$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultCOST[2,12] <- (sum(UniversalTestAndTreat_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment

####################
### MULTIVARIATE ###
####################

# To simulate multivariate analysis run './scripts/multivariate-control.py'

setwd("/path/to/multivariate/results")

run <- c("run1","run2","run3","run4","run5","run6","run7","run8","run9","run10")
interventions <- c("Multi_2","Multi_3","Multi_4","Multi_5","ImmediateArtAndMulti_5","UttAndMulti_5")

# Again these loops load the simulations and repeat runs, and averages across them all.
for(i in 1:length(interventions)) {
    cat(paste("",interventions[i], "\n"))
    # Create vector of names
    outputNames <- c()
    for(m in 1:length(Baseline))
        outputNames[m] <- names(Baseline)[m]
    # Create list
    output <- sapply(outputNames,function(x) NULL)
    for(n in 1:length(output))
        output[[n]] <- vector('double',length(Baseline[[n]]))
    theLength = 0
    for(j in 1:length(run)) {
        if(file.exists(gsub(" ","",paste("./",run[j],"/output/",interventions[i],"/currentWorkspace.RData")))) {
            load(gsub(" ","",paste("./",run[j],"/output/",interventions[i],"/currentWorkspace.RData")))
            cat(paste("\t",run[j], "\n"))
            theLength <- theLength + 1
            for(k in 1:length(get(interventions[i]))) {
                output[[k]] <- output[[k]] + get(interventions[i])[[k]]
            }
        }
    }
    cat(paste("\t\t\ttheLength =",theLength, "\n"))
    for(l in 1:length(get(interventions[i]))) {
        output[[l]] <- output[[l]] / theLength
    }
    assign(interventions[i],output)
}
print("\tComplete!")

resultMultiVariate <- matrix(0,2,7)
resultMultiVariate[1,1] <- (sum(Baseline$sDALY) - sum(Linkage_2$sDALY)) * sizeAdjustment
resultMultiVariate[1,2] <- (sum(Baseline$sDALY) - sum(Multi_2$sDALY)) * sizeAdjustment
resultMultiVariate[1,3] <- (sum(Baseline$sDALY) - sum(Multi_3$sDALY)) * sizeAdjustment
resultMultiVariate[1,4] <- (sum(Baseline$sDALY) - sum(Multi_4$sDALY)) * sizeAdjustment
resultMultiVariate[1,5] <- (sum(Baseline$sDALY) - sum(Multi_5$sDALY)) * sizeAdjustment
resultMultiVariate[1,6] <- (sum(Baseline$sDALY) - sum(ImmediateArtAndMulti_5$sDALY)) * sizeAdjustment
resultMultiVariate[1,7] <- (sum(Baseline$sDALY) - sum(UttAndMulti_5$sDALY)) * sizeAdjustment

resultMultiVariate[2,1] <- (sum(Linkage_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,2] <- (sum(Multi_2$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,3] <- (sum(Multi_3$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,4] <- (sum(Multi_4$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,5] <- (sum(Multi_5$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,6] <- (sum(ImmediateArtAndMulti_5$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment
resultMultiVariate[2,7] <- (sum(UttAndMulti_5$sCOST) - sum(Baseline$sCOST)) * sizeAdjustment

################
### FIGURE 2 ###
################

library(RColorBrewer)
m <- brewer.pal(11,"Spectral")
p <- brewer.pal(9,"Set1")
require(plotrix)

graphics.off()
adjustWeight = 0.75
quartz.options(h=5 * adjustWeight,w=8 * adjustWeight)


par(family="Arial",cex=1,mar=c(2,2,2,2))
plot.new()
bisect.angles <- floating.pie(0,0,Baseline$sCARE,startpos=pi/2)
pie(Baseline$sCARE,
    init.angle=90,
    labels=c("Never tested",
            "Tested but never\nlinked to care",
            "Tested and linked, but\n never initiated ART",
            "Initiated ART but died\nfollowing late initiation (<200)",
            "Initiated ART but\ndied off ART",
            "Initiatied ART but\nnot late (>200)"),
    col=c(m[1:6]),
    border=NA,
    cex.main=1,
    cex=0.7)
pie.values <- gsub(" ","",paste(round(Baseline$sCARE / sum(Baseline$sCARE),2) * 100,"%"))
par(family="Arial Bold",cex=1)
pie.labels(0,0,bisect.angles,pie.values,radius=0.45)

quartz.save(file='./plots/Fig2.pdf',type='pdf')

################
### FIGURE 3 ###
################

Dalys <- c(resultDALY[2,1],resultDALY[2,2],resultDALY[2,3],resultDALY[2,4],resultDALY[1,5],resultDALY[2,6],resultDALY[2,7],resultDALY[1,8],resultDALY[2,9],resultDALY[2,10],resultDALY[1,11],resultDALY[2,12],resultMultiVariate[1,5],resultMultiVariate[1,6])
Cost <- c(resultCOST[2,1],resultCOST[2,2],resultCOST[2,3],resultCOST[2,4],resultCOST[1,5],resultCOST[2,6],resultCOST[2,7],resultCOST[1,8],resultCOST[2,9],resultCOST[2,10],resultCOST[1,11],resultCOST[2,12],resultMultiVariate[2,5],resultMultiVariate[2,6])
Interventions <- c("HBCT","Enhanced CT","HBCT (with POC CD4)","Facilitated Linkage","VCT POC CD4","Pre-ART Outreach","Improved Care","POC CD4","On-ART Outreach","Adherence","Immediate ART","Universal Test & Treat","Optimal Combination","Optimal Combination + Immediate ART")
Scenario <- c("Real","Real","Real","Real","Max","Real","Real","Max","Real","Real","Max","Real","Combo","Combo")
Color <- c(plotCol[1],plotCol[2],plotCol[3],plotCol[4],plotCol[5],plotCol[6],plotCol[7],plotCol[8],plotCol[9],plotCol[10],plotCol[11],plotCol[12],"grey",1)
Iteration <- "mean"
results <- data.frame(Interventions,Scenario,Dalys,Cost,Color,Iteration)
results$Interventions <- factor(results$Interventions, levels=c("HBCT","Enhanced CT","HBCT (with POC CD4)","Facilitated Linkage","VCT POC CD4","Pre-ART Outreach","Improved Care","POC CD4","On-ART Outreach","Adherence","Immediate ART","Universal Test & Treat","Optimal Combination","Optimal Combination + Immediate ART"))
results <- mutate(results,label = c("HBCT","CT","HBCT (with POC CD4)","Linkage","VCT POC CD4","Pre-ART Outreach","Improved Care","POC CD4","On-ART Outreach","Adherence","Immediate ART","Universal Test & Treat","Optimal Combination","Optimal Combination + Immediate ART"))
results

# Load some packages
require(ggplot2)
require(RColorBrewer)
require(scales)
library(grid)

# Reset graphics device
graphics.off()
adjustWeight = 0.75
quartz.options(h=5 * adjustWeight,w=8 * adjustWeight)

# Create ggplot
p <- ggplot(results,aes(x=Dalys, y=Cost, fill=Interventions, label=Interventions))
p <- p + geom_point(col=Color,alpha=1, size=2, shape=16)
p <- p + theme_classic()
p <- p + scale_x_continuous(limits=c(0,2e+06), breaks=seq(0,2e+06,5e+05),labels=scientific,expand=c(0,0))
p <- p + scale_y_continuous(limits=c(0,3e+09), breaks=seq(0,3e+09,5e+08),labels=scientific,expand=c(0,0))
p <- p + xlab("DALYs averted")
p <- p + ylab("Additional cost (2013 USD)")
p <- p + theme(plot.title=element_text(size=7,face='bold'))
p <- p + theme(axis.title=element_text(size=8))
p <- p + theme(axis.text=element_text(size=7))
p <- p + theme(legend.position=c(0.45,0.275))
p <- p + theme(legend.title=element_blank())
p <- p + theme(legend.text=element_text(size=7))
p <- p + theme(legend.justification=c(1,0))
p <- p + theme(legend.key = element_blank())
p <- p + theme(legend.key.size = unit(0.35, "cm"))
p <- p + theme(plot.margin = unit(c(0.35, 1, 0.3, 0.35), "cm"))
p

quartz.save(file='./plots/Fig3.pdf',type='pdf')

############
# FIGURE 4 #
############

library(RColorBrewer)
o <- brewer.pal(11,"Spectral")

# Load the relevant mortality data.
mortalityPlot <- as.matrix(data.frame(Baseline$sCARE,ImmediateArt$sCARE,Multi_5$sCARE,UniversalTestAndTreat_2$sCARE,ImmediateArtAndMulti_5$sCARE,UttAndMulti_5$sCARE))

graphics.off()
adjustWeight = 0.7
quartz.options(h=8 * adjustWeight,w=8 * adjustWeight)

par(family="Arial")
    barplot(mortalityPlot * sizeAdjustment,
        col=c(o[1:6]),
        cex.main=0.8,
        cex.lab=0.8,
        space=c(0.5),
        border=NA,
        ylim=c(0,9e+05),
        ylab="HIV-related deaths between 2010 and 2030",
        yaxt='n',
        xaxt='n')
axis(2,at=seq(0,9e+05,1e+05),labels=c(" ",format(seq(1e+05,9e+05,1e+05),big.mark=",",scientific=FALSE)),las=3,cex.axis=0.55)
axis(2,at=0,labels=0,hadj=c(0.5),cex.axis=0.55)

mtext("Baseline",1,at=1,0.6,cex=0.5)
mtext("Immediate\nART",1,at=2.5,0.75,cex=0.5)
mtext("Combination of\ninterventions",1,at=4,0.75,cex=0.5)
mtext("Immediate ART &\n HBCT (UTT)",1,at=5.5,0.75,cex=0.5)
mtext("Immediate ART &\n combination of\n interventions",1,at=7,1,cex=0.5)
mtext("UTT &\n combination of\n interventions",1,at=8.5,1,cex=0.5)

labels=c("Never tested", "Tested but never linked to care", "Tested and linked, but never initiated ART", "Initiated ART but died following late initiation (<200)", "Initiated ART but died off ART", "Initiatied ART but not late (>200)")
legend("topright",
    labels,
    fill=c(o[1:6]),
    cex=0.6,
    box.lty=0)

text(1,(sum(mortalityPlot[,1]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(Baseline$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)
text(2.5,(sum(mortalityPlot[,2]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(ImmediateArt$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)
text(4,(sum(mortalityPlot[,3]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(Multi_5$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)
text(5.5,(sum(mortalityPlot[,4]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(UniversalTestAndTreat_2$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)
text(7,(sum(mortalityPlot[,5]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(ImmediateArtAndMulti_5$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)
text(8.5,(sum(mortalityPlot[,6]) * sizeAdjustment) + 2e+04,gsub(" ","",paste(dollar((sum(UttAndMulti_5$sCOST) * sizeAdjustment)  / 1e+9),"b")),cex=0.5)

quartz.save(file='./plots/Fig4.pdf',type='pdf')