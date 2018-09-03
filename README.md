# -
数据结构的代码C++实现
主要用于课外知识的补充分析

贝叶斯估计是最大后验估计的进一步扩展，贝叶斯估计同样假定$\theta$是一个随机变量，但贝叶斯估计并不是直接估计出$\theta$的某个特定值，而是估计$\theta$的分布，这是贝叶斯估计与最大后验概率估计不同的地方。在贝叶斯估计中，先验分布$P(X)$是不可忽略的。回到抛硬币的例子中，在已知$X$的情况下，描述$\theta$的分布即描述$P(\theta|X)$，$P(\theta|X)$是一种后验分布。如果后验分布的范围较窄，则估计值的准确度相对较高，反之，如果后验分布的范围较广，则估计值的准确度就较低。

贝叶斯公式：$$P(\theta|X)=\frac {P(X|\theta)P(\theta)} {P(X)}$$

在连续型随机变量中，由于$P(X)=\int_{\Theta}P(X|\theta)P(\theta)d\theta$，因此贝叶斯公式变为：$$P(\theta|X)=\frac {P(X|\theta)P(\theta)} {\int_{\Theta}P(X|\theta)P(\theta)d\theta}$$

从上面的公式中可以看出，贝叶斯估计的求解非常复杂，因此选择合适的先验分布就非常重要。一般来说，计算积分$\int_{\theta}P(X|\theta)P(\theta)d\theta$是不可能的。对于这个抛硬币的例子来说，如果使用共轭先验分布，就可以更好的解决这个问题。二项分布参数的共轭先验是Beta分布，由于$\theta$的似然函数服从二项分布，因此在贝叶斯估计中，假设$\theta$的先验分布服从$P(\theta)\sim Beta(\alpha, \beta)$，Beta分布的概率密度公式为：$$f(x;\alpha,\beta)=\frac {1} {B(\alpha,\beta)}x{\alpha-1}(1-x){\beta-1}$$因此，贝叶斯公式可写作：$$\begin{aligned} P(\theta|X)&=\frac {P(X|\theta)P(\theta)} {\int_{\Theta}P(X|\theta)P(\theta)d\theta} \\ &=\frac {\theta6(1-\theta)4 \frac {\theta{\alpha-1}(1-\theta){\beta-1}} {B(\alpha,\beta)} } {\int_{\Theta}\theta6(1-\theta)4 \frac {\theta{\alpha-1}(1-\theta){\beta-1}} {B(\alpha,\beta)}d\theta} \\&=\frac {\theta{\alpha+6-1}(1-\theta){\beta+4-1}} {\int_{\Theta}\theta{\alpha+6-1}(1-\theta){\beta+4-1}d\theta} \\
&=\frac {\theta{\alpha+6-1}(1-\theta){\beta+4-1}} {B(\alpha+6-1,\beta+4-1)} \\
&=Beta(\theta|\alpha+6-1,\beta+4-1) \\&=Beta(\theta|\alpha+6,\beta+4)\end{aligned}$$从上面的公式可以看出，$P(\theta|X) \sim Beta(\theta|\alpha+6,\beta+4)$。其中$B$函数，也称$Beta$函数，是一个标准化常量，用来使整个概率的积分为1。$Beta(\theta|\alpha+6,\beta+4)$就是贝叶斯估计的结果。

如果使用贝叶斯估计得到的$\theta$分布存在一个有限均值，则可以用后验分布的期望作为$\theta$的估计值。假设$\alpha=3,\beta=3$，在这种情况下，先验分布会在$0.5$处取得最大值，则$P(\theta|X) \sim Beta(\theta|9,7)$，$Beta(\theta|9,7)$的曲线如下图：
