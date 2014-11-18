evaluate<-function(w, x) {
    return (sign(w[1]*x[1] + w[2]*x[2] +w[3]))
}

plotline<-function(w) {
    m = -w[2]/w[1]
    b = -w[3]/w[1]
    x = seq(-1,1,0.1)
    y = m*x + b
    plot(x, y, ylim=range(c(-1,1)), xlim=(c(-1,1)), t="n")
    lines(x,y)
    par(new = TRUE)
}

PLA = function(training, target)
{
    converge = FALSE
    iteration = 0
    w = c(0,0,0)
    while (iteration<10000 && !converge) {
        iteration = iteration+1;
        miss = c(0)
        for(i in 1:nrow(training)) {
            if(evaluate(w, training[i,]) != evaluate(target, training[i,]))
                miss = cbind(miss,i)
        }
        converge = length(miss) <= 1
        if(!converge) {
            #index = sample(miss[2:length(miss)],1)
            index = miss[2]
            s = evaluate(target, training[index,])
            w[1] = w[1] + s*training[index,1]
            w[2] = w[2] + s*training[index,2]
            w[3] = w[3] + s
        }
    }

    return (list(w=w, iteration=iteration))
}

## Function to generate the data
generate = function(N = 10, ext = 1) {
    x1 = runif(N, -ext, ext)
    x2 = runif(N, -ext, ext)

    point = runif(2, -ext, ext)
    point2 = runif(2, -ext, ext)
    slope = (point2[2] - point[2]) / (point2[1] - point[1])
    intercept = point[2] - slope * point[1]
    w = c(slope, -1, intercept)
    data = cbind(x1,x2)
    return(list(data = data, w = w))
}

disagree <- function(w1, w2, N=1000){
    x1 = runif(N, -1, 1)
    x2 = runif(N, -1, 1)
    disagreement = 0
    for(i in 1:length(x1)) {
        x = cbind(x1[i], x2[i])
        if (evaluate(w1,x) != evaluate(w2,x))
            disagreement = disagreement + 1
    }
    return (disagreement/N)
}

SVM <- function(X, target) {
    N = nrow(X)
    Y = rep(0,N)
    for(i in 1:N) {
        Y[i] = evaluate(target, X[i,])
    }
    Vmat = matrix(0,N,N)
    for(i in 1:N) {
        for(j in 1:N)
        Vmat[i,j] = Y[i]*Y[j]*sum(t(X[i,])*X[j,])
    }
    dvec = rep(-1, N)
    Amat = t(Y)
    uvec = rep(1000, N)
    
    sol = LowRankQP(Vmat=Vmat,dvec=dvec,Amat=Amat,bvec=0,uvec=uvec,method="LU")
    alpha = sol$alpha
    #look for a non zero alpha
    alpha = zapsmall(alpha, digits=6)
    numAlfas = sum(alpha>0)
    a = 0
    counter = 0
    for(i in 1:length(alpha)) {
        if (alpha[i] != 0) {
            a = alpha[i]
            counter = i
            break()
        }   
    }

    w = c(0,0)
    for(j in 1:nrow(X)) {
        w =  w + alpha[j]*Y[j]*X[j,]
    }

    b = 1/Y[counter] - sum(w*X[counter,])
    return (list(w = cbind(t(w), b), numAlfas = numAlfas))
    #return (cbind(t(w), b))
}


exercise8<-function() {
    PLAwin=0;
    SVMwin=0
    N = 1000
    for(i in 1:N) {
        data = generate()
        Gpla = PLA(data$data, data$w)
        Gsvm = SVM(data$data, data$w)
        plaerror = disagree(data$w, Gpla$w)
        svmerror = disagree(data$w, Gsvm$w)
        if (plaerror < svmerror)
           PLAwin = PLAwin + 1 
    }
    print("PLA score")
    print(PLAwin/N)
    print("SVM score")
    print((N-PLAwin)/N)    
}

exercise9<-function() {
    PLAwin=0;
    SVMwin=0
    N = 1000
    alphas = 0
    for(i in 1:N) {
        data = generate(100)
        Gpla = PLA(data$data, data$w)
        Gsvm = SVM(data$data, data$w)
        plaerror = disagree(data$w, Gpla$w,10000)
        svmerror = disagree(data$w, Gsvm$w,10000)
        if (plaerror < svmerror)
           PLAwin = PLAwin + 1
        alphas = alphas + Gsvm$numAlfas
    }
    print("PLA score")
    print(PLAwin/N)
    print("SVM score")
    print((N-PLAwin)/N)
    print("Alphas non zero")
    print(alphas/N)
}
