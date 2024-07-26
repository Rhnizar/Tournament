models
from django.db import models

class Tournament(models.Model):
    name = models.CharField(max_length=255)
    start_date = models.DateField()
    end_date = models.DateField()
    num_players = models.IntegerField()
    
    # Stage date fields
    round_of_16_date = models.DateField(null=True, blank=True)
    quarterfinals_date = models.DateField(null=True, blank=True)
    semifinals_date = models.DateField(null=True, blank=True)
    final_date = models.DateField(null=True, blank=True)

    def __str__(self):
        return self.name

    def get_stages(self):
        # Determine which stages are applicable based on the number of players
        stages = []
        if self.num_players == 4:
            if self.semifinals_date:
                stages.append(('Semifinals', self.semifinals_date))
            if self.final_date:
                stages.append(('Final', self.final_date))
        elif self.num_players == 8:
            if self.quarterfinals_date:
                stages.append(('Quarterfinals', self.quarterfinals_date))
            if self.semifinals_date:
                stages.append(('Semifinals', self.semifinals_date))
            if self.final_date:
                stages.append(('Final', self.final_date))
        elif self.num_players == 16:
            if self.round_of_16_date:
                stages.append(('Round of 16', self.round_of_16_date))
            if self.quarterfinals_date:
                stages.append(('Quarterfinals', self.quarterfinals_date))
            if self.semifinals_date:
                stages.append(('Semifinals', self.semifinals_date))
            if self.final_date:
                stages.append(('Final', self.final_date))
        return stages


from django.db import models

class Stage(models.Model):
    STAGE_CHOICES = [
        ('ROUND_16', 'Round of 16'),
        ('QUARTERFINALS', 'Quarterfinals'),
        ('SEMIFINALS', 'Semifinals'),
        ('FINAL', 'Final'),
    ]
    
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE)
    stage_type = models.CharField(max_length=20, choices=STAGE_CHOICES)
    date = models.DateField()

    def __str__(self):
        return f"{self.get_stage_type_display()} - {self.date}"

class Player(models.Model):
    name = models.CharField(max_length=255)
    # Other player fields here

class StagePlayer(models.Model):
    stage = models.ForeignKey(Stage, related_name='players', on_delete=models.CASCADE)
    player = models.ForeignKey(Player, on_delete=models.CASCADE)

    def __str__(self):
        return f"{self.player.name} in {self.stage.get_stage_type_display()}"



# code 

from django.shortcuts import render, redirect
from .models import Tournament, Stage, StagePlayer, Player

def create_tournament(request):
    if request.method == 'POST':
        name = request.POST['name']
        start_date = request.POST['start_date']
        end_date = request.POST['end_date']
        num_players = int(request.POST['num_players'])

        round_of_16_date = request.POST.get('round_of_16_date')
        quarterfinals_date = request.POST.get('quarterfinals_date')
        semifinals_date = request.POST.get('semifinals_date')
        final_date = request.POST.get('final_date')

        tournament = Tournament.objects.create(
            name=name,
            start_date=start_date,
            end_date=end_date,
            num_players=num_players,
            round_of_16_date=round_of_16_date if num_players == 16 else None,
            quarterfinals_date=quarterfinals_date if num_players >= 8 else None,
            semifinals_date=semifinals_date if num_players >= 4 else None,
            final_date=final_date if num_players >= 4 else None
        )
        
        stages = tournament.get_stages()
        
        for stage_name, stage_date in stages:
            stage = Stage.objects.create(
                tournament=tournament,
                stage_type=stage_name.replace(' ', '_').upper(),
                date=stage_date
            )
            
            # Here you should implement logic to assign players to this stage
            # For example, you could assign players to the stage based on the number of players required

        return redirect('tournament_detail', tournament_id=tournament.id)
    
    return render(request, 'create_tournament.html')
