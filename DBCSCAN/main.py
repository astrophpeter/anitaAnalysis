import csv
import pandas as pd, numpy as np, matplotlib.pyplot as plt, time
from sklearn.cluster import DBSCAN
from sklearn import metrics
from geopy.distance import great_circle
from shapely.geometry import MultiPoint
from sklearn.cluster import DBSCAN
from sklearn import metrics
from sklearn.datasets.samples_generator import make_blobs
from sklearn.preprocessing import StandardScaler
from matplotlib.ticker import NullFormatter,MultipleLocator, FormatStrFormatter
import matplotlib.gridspec as gridspec
plt.style.use('idl.mplstyle')


# define the number of kilometers in one radian
kms_per_radian = 6371.0088

# load the data set
df = pd.read_csv('EventRun16k.csv', encoding='utf-8')
df.head()
fracs = []
radii = []

WAIS = False

# represent points consistently as (lat, lon)
coords = df.as_matrix(columns=['lat', 'lon'])

total = df.as_matrix(columns=['eventNum','run','priority','theta'])

run = df.as_matrix(columns=['run'])

size = len(coords)
percentOfTotal = 100.0
radius = 0.0
count = 0.0

if (WAIS) :
    while (percentOfTotal > 0.0001):
        radius += 1

        # define epsilon as 1.5 kilometers, converted to radians for use by haversine
        epsilon = radius / kms_per_radian

        db = DBSCAN(eps=epsilon, min_samples=2, algorithm='ball_tree', metric='haversine').fit(np.radians(coords))
        core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
        core_samples_mask[db.core_sample_indices_] = True
        labels = db.labels_

        # Number of clusters in labels, ignoring noise if present.
        #n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)


        UHEN = (labels == -1)
   
        percentOfTotal = float(len(coords[UHEN])) / size
    
        radii.append(radius)
        fracs.append(1 - (float(len(coords[UHEN])) / size))
    
        if (count ==0 and percentOfTotal > 0.999):
                usedRadius = radius
                count += 1

  
        print('Radius: %d' % radius)
 
        print(1 - (float(len(coords[UHEN])) / size))
    
        #print("Homogeneity: %0.3f" % metrics.homogeneity_score(labels_true, labels))
        #print("Completeness: %0.3f" % metrics.completeness_score(labels_true, labels))
        #print("V-measure: %0.3f" % metrics.v_measure_score(labels_true, labels))
        #print("Adjusted Rand Index: %0.3f"
        #      % metrics.adjusted_rand_score(labels_true, labels))
        #print("Adjusted Mutual Information: %0.3f"
        #        % metrics.adjusted_mutual_info_score(labels_true, labels))
        #print("Silhouette Coefficient: %0.3f"
        #       % metrics.silhouette_score(np.radians(coords), labels))

    print(radii,fracs)
    plt.xscale('log')
    plt.yscale('log')
    plt.axvline(x=usedRadius)
    plt.ayvline(y=99.9)
    
    plt.ylabel('Fraction of WAIS Pulsers identified as Clustered')
    plt.xlabel('Characteristic Unit Clustering Radius [km]')
    plt.plot(radii,fracs)
    plt.show()
else :
    radius = 80.0
    epsilon = radius / kms_per_radian
    db = DBSCAN(eps=epsilon, min_samples=2, algorithm='ball_tree', metric='haversine').fit(np.radians(coords))
    core_samples_mask = np.zeros_like(db.labels_, dtype=bool)
    core_samples_mask[db.core_sample_indices_] = True
    labels = db.labels_

    UHEN = (labels == -1)
    print('Number of Isolated Events: %d' % len(coords[UHEN]))
    print('Clustering radis used: %d km' % radius)



    n_clusters_ = len(set(labels)) - (1 if -1 in labels else 0)
    # Black removed and is used for noise instead.
    unique_labels = set(labels)
    colors = plt.cm.Spectral(np.linspace(0, 1, len(unique_labels)))
    for k, col in zip(unique_labels, colors):
        if k == -1:
            # Black used for noise.
            col = 'k'
        else:
            col = 'r'

        class_member_mask = (labels == k)
        Outlier_member_mask = (labels == -1)

        xy = coords[class_member_mask & core_samples_mask]
        plt.plot(xy[:, 0], xy[:, 1], 'o', markerfacecolor=col,
        markeredgecolor=col, markersize=2,alpha=0.05)
   
        xy = coords[class_member_mask & ~core_samples_mask & ~Outlier_member_mask]
        plt.plot(xy[:, 0], xy[:, 1], 'o', markerfacecolor=col,
        markeredgecolor=col, markersize=1,alpha=0.05)

        xy = coords[class_member_mask & ~core_samples_mask & Outlier_member_mask]
        plt.plot(xy[:, 0], xy[:, 1], 'o',marker="*", markerfacecolor=col,
        markeredgecolor=col, markersize=3)


    plt.xlabel('Latitude')
    plt.ylabel('Longitude')
    plt.title('Red: Cluster Member, Black: Isolated %d' % len(coords[UHEN]))
    plt.show()

with open('isolated.csv', 'w',newline='') as csvfile:
    out = csv.writer(csvfile,delimiter=',')
    out.writerows(total[UHEN])


 

