{if count($projects) > 0}
<table align="center" width="85%">
    <thead>
        <tr>
            <td>_("Project name")</td>
            <td>_("Project time")</td>
            <td>_("Project location")</td>
            <td>_("Project manager")</td>
            <td>_("Volunteers need")</td>
            <td>_("Volunteers assigned")</td>
        </tr>
    </thead>
    <tbody>
        {foreach $projects as $project}
        <tr>
            <td>
                <a href='?mod=vm&act=project&vm_action=display_closure_report&proj_id={$project.id}'>{$project.name}</a>
                {if $project['p_uuid'] == $p_uuid}
                <br /><a href='?mod=vm&act=project&vm_action=display_closure_edit&proj_id={$project.id}'>[_("Edit closure report")]</a>
                {/if}
            </td>
            <td>{$project.time}</td>
            <td>{$project.location}</td>
            <td>{$project.projectManager}</td>
            <td>{$project.requiredVolunteers}</td>
            <td>{$project.numVolunteers}</td>
        </tr>
        {/foreach}
    </tbody>
</table>
{else}
<center>(_("no projects"))</center>
{/if}
<br />